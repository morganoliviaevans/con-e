from PIL import Image
from enum import Enum
import numpy as np
import cv2
import serial
import time


class Direction(Enum):
    STOP = 0
    ROTATE_LEFT = 1
    ROTATE_RIGHT = 2
    SPIN = 3
    FORWARD = 4
    BACKWARD = 5


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
        return Direction.RIGHT
    elif midpoint >= 500:
        return Direction.LEFT
    else:
        return Direction.STOP


def area(x1, x2, y1, y2):
    return (x2 - x1) * (y2 - y1)


def loop(cam, arduino):
    # TODO: fine tune the area threshold
    AREA_LOWER_THRESHOLD = 70000
    AREA_UPPER_THRESHOLD = 130000
    orange = [12, 95, 247]

    while True:
        ret, frame = cam.read()
        cv2.normalize(frame, frame, 0, 255, cv2.NORM_MINMAX)

        hsvImage = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        lowerLimit, upperLimit = get_limits(orange)

        mask = cv2.inRange(hsvImage, lowerLimit, upperLimit)

        mask_ = Image.fromarray(mask)

        bbox = mask_.getbbox()

        if bbox is not None:
            x1, y1, x2, y2 = bbox

            bbox_area = area(x1, x2, y1, y2)
            print(bbox_area)

            if bbox_area < AREA_LOWER_THRESHOLD:
                direction = Direction.FORWARD
            elif bbox_area > AREA_UPPER_THRESHOLD:
                direction = Direction.BACKWARD
            else:
                direction = get_direction(y1, y2)

            frame = cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 5)

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

        cv2.imshow("frame", mask)
        cv2.imshow("original", frame)

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
