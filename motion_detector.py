import cv2
import datetime
import imutils
import time

camera = cv2.VideoCapture(0)


firstFrame = None
min_area = 400


while True:
    (grabbed, frame) = camera.read()
    text = "Unoccupied"

    if not grabbed:
        break

    frame = imutils.resize(frame ,width=500)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (21,21), 0)

    if firstFrame is None:
        firstFrame = gray
        continue

    frameDelta = cv2.absdiff(firstFrame, gray)
    thresh = cv2.threshold(frameDelta, 150, 255, cv2.THRESH_BINARY)[1]

    thresh = cv2.dilate(thresh, None, iterations=2)
    im,cnts,heirachy = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
                cv2.CHAIN_APPROX_SIMPLE)
    text = "Unoccupied"
    for c in cnts:
    	print(cv2.contourArea(c))
        if cv2.contourArea(c) < min_area or cv2.contourArea(c) > 50000:
            continue

        (x, y, w, h) = cv2.boundingRect(c)
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        text = "Occupied"

    cv2.putText(frame, "Room Status: {}".format(text), (10,20),
    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
        
    cv2.putText(frame, datetime.datetime.now().strftime("%A %d %B %Y %I:%M:%S%p"),
		(10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)
    
    cv2.imshow('Frame',frame)
       
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


camera.release()
cv2.destroyAllWindows()
