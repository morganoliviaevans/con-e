from PIL import Image
from enum import Enum
import numpy as np
import random
import cv2
import serial
import time


class DeviceState(Enum):
    PLAY_CAMERA = 0
    PLAY_REMOTE = 1
    IDLE = 2
    SLEEP = 3


class Direction(Enum):
    STOP = 0
    ROTATE_LEFT = 1
    ROTATE_RIGHT = 2
    SPIN = 3
    FORWARD = 4
    BACKWARD = 5


currentState = DeviceState.IDLE

# TODO: fine tune the area threshold
AREA_LOWER_THRESHOLD = 40000
AREA_UPPER_THRESHOLD = 130000


def get_limits(color):
    c = np.uint8([[color]])
    hsvC = cv2.cvtColor(c, cv2.COLOR_BGR2HSV)

    # calculate tolerances for the orange
    lowerLimit = hsvC[0][0][0] - 10, 120, 200
    upperLimit = hsvC[0][0][0] + 10, 255, 255

    lowerLimit = np.array(lowerLimit, dtype=np.uint8)
    upperLimit = np.array(upperLimit, dtype=np.uint8)

    return lowerLimit, upperLimit


def get_direction(y1, y2):
    midpoint = (y1 + (y1 + y2)) / 2

    if midpoint < 100:
        return Direction.ROTATE_RIGHT
    elif midpoint >= 500:
        return Direction.ROTATE_LEFT
    else:
        return Direction.STOP


def area(x1, x2, y1, y2):
    return (x2 - x1) * (y2 - y1)


def loop(cam, arduino):
    global currentState
    orange = [12, 95, 247]

    # Last State
    lastSeen = time.time()
    lastSeenOrange = None

    # Last time since random sound effect
    lastSoundEffect = time.time() + random.randint(30, 60)

    while True:
        direction = Direction.STOP
        # OpenCV stuff
        ret, frame = cam.read()
        cv2.normalize(frame, frame, 0, 255, cv2.NORM_MINMAX)

        hsvImage = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        lowerLimit, upperLimit = get_limits(orange)

        mask = cv2.inRange(hsvImage, lowerLimit, upperLimit)
        mask_ = Image.fromarray(mask)
        bbox = mask_.getbbox()

        if bbox is not None:
            lastSeen = time.time()
            x1, y1, x2, y2 = bbox

            bbox_area = area(x1, x2, y1, y2)
            print(bbox_area)

            orientation = get_direction(y1, y2)

            if bbox_area < AREA_LOWER_THRESHOLD and orientation is Direction.STOP:
                direction = Direction.FORWARD
            elif bbox_area > AREA_UPPER_THRESHOLD and orientation is Direction.STOP:
                direction = Direction.BACKWARD
            else:
                direction = orientation

            frame = cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 5)

            # Go back to play state if orange for >= 5s
            if lastSeenOrange is None:
                lastSeenOrange = time.time()
            elif time.time() - lastSeenOrange >= 5:
                if currentState != DeviceState.PLAY_CAMERA:
                    arduino.write(b"a")
                    print("going back to play_camera")
                    currentState = DeviceState.PLAY_CAMERA
        # if bbox is None
        else:
            lastSeenOrange = None
            elapsed = time.time() - lastSeen

            if elapsed > 30:
                if currentState != DeviceState.SLEEP:
                    arduino.write(b"z")
                    print("sleeping")
                    currentState = DeviceState.SLEEP
            elif elapsed > 15:
                if currentState != DeviceState.IDLE:
                    arduino.write(b"i")
                    print("idling")
                    currentState = DeviceState.IDLE

        # show cv frames
        cv2.imshow("frame", mask)
        cv2.imshow("original", frame)

        # Check the state of the device
        match currentState:
            case DeviceState.PLAY_CAMERA:
                # Send signal for random sound effect
                if time.time() >= lastSoundEffect:
                    arduino.write(b"m")
                    print("sent random sound effect")
                    lastSoundEffect = time.time() + random.randint(30, 60)

                # do something based off the direction
                match direction:
                    case Direction.FORWARD:
                        arduino.write(b"f")
                        print("forward")
                    case Direction.BACKWARD:
                        arduino.write(b"b")
                        print("backward")
                    case Direction.STOP:
                        arduino.write(b"s")
                        print("stop")
                    case Direction.ROTATE_LEFT:
                        arduino.write(b"l")
                        print("left")
                    case Direction.ROTATE_RIGHT:
                        arduino.write(b"r")
                        print("right")
            case DeviceState.IDLE:
                arduino.write(b"s")
                print("in idle state")
            case DeviceState.SLEEP:
                print("sleeping")

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cam.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    cam = cv2.VideoCapture(0)
    arduino = serial.Serial("/dev/ttyUSB0", 9600)
    time.sleep(2)

    try:
        loop(cam, arduino)
    except KeyboardInterrupt:
        cam.release()
        cv2.destroyAllWindows()
