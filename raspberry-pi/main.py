from enum import Enum
import numpy as np
import cv2
import serial
import time


class Direction(Enum):
    CENTER = 0
    LEFT = 1
    RIGHT = 2
    ROTATE_LEFT = 3
    ROTATE_RIGHT = 4
    SPIN = 5


def get_limits(color):
    c = np.uint8([[color]])
    hsvC = cv2.cvtColor(c, cv2.COLOR_BGR2HSV)

    # calculate tolerances for the orange
    lowerLimit = hsvC[0][0][0] - 10, 100, 100
    upperLimit = hsvC[0][0][0] + 10, 255, 255

    lowerLimit = np.array(lowerLimit, dtype=np.uint8)
    upperLimit = np.array(upperLimit, dtype=np.uint8)

    return lowerLimit, upperLimit


def get_direction(x1, y1, x2, y2):
    midpoint = (x1 + (x1 + x2)) / 2

    if midpoint < 200:
        return Direction.RIGHT
    elif midpoint >= 400:
        return Direction.LEFT
    else:
        return Direction.CENTER


def loop(cam, arduino):
    orange = [12, 95, 247]

    while True:
        ret, frame = cam.read()

        hsvImage = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        lowerLimit, upperLimit = get_limits(orange)

        mask = cv2.inRange(hsvImage, lowerLimit, upperLimit)

        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        if contours:
            largest_contour = max(contours, key=cv2.contourArea)

            # draw box around the largest contour
            x1, y1, x2, y2 = cv2.boundingRect(largest_contour)
            cv2.rectangle(frame, (x1, y2), (x1 + x2, y1 + y2), (0, 255, 0), 2)

            direction = get_direction(x1, y1, x2, y2)

            # do something based off the direction
            match direction:
                case Direction.CENTER:
                    arduino.write(b"s")
                    print("center")
                case Direction.LEFT:
                    arduino.write(b"l")
                    print("left")
                case Direction.RIGHT:
                    arduino.write(b"r")
                    print("right")

        cv2.imshow("frame", frame)

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
