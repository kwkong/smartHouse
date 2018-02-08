import numpy as np
import cv2
import requests
import json
#import pyttsx
import time

import base64
import imutils


cap = cv2.VideoCapture(1)
address = 'http://172.16.192.148/ESPsmartHouse/ESPsmartHouse.php?face='
server_addr = 'http://172.16.192.170:5000'
test_url = server_addr + '/api/test'

content_type = 'image/jpeg'
headers = {'content-type': content_type}

current_milli_time = lambda: int(round(time.time() * 1000))

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')
#engine = pyttsx.init()
last_spoke_time = current_milli_time()
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    if ret == True:
       # print(frame.size)
        # Our operations on the frame come here
        orig_frame = frame.copy()
        orig_width = orig_frame.shape[1]
        orig_height = orig_frame.shape[0]
        frame = imutils.resize(frame,width=100,height=100)
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)

        for (x,y,w,h) in faces:
            x_n = x / float(frame.shape[1])
            w_n = w / float(frame.shape[1])
            y_n  = y / float(frame.shape[0])
            h_n  = h / float(frame.shape[0])
            x = int(x_n * orig_width)
            y = int(y_n * orig_height)
            w = int(w_n * orig_width)
            h = int(h_n * orig_height)
            cv2.rectangle(orig_frame,(x,y),(x+w,y+h),(255,0,0),2) 
            #roi_gray = gray[y:y+h, x:x+w]
            #roi_color = frame[y:y+h, x:x+w]
            #eyes = eye_cascade.detectMultiScale(roi_gray)
            #for (ex,ey,ew,eh) in eyes:
            #    cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
        
    
        if len(faces)  > 0:
            r = requests.get(address+'1')
            if((current_milli_time() - last_spoke_time) > 2000):
                #engine.say('let me out')
	            #engine.runAndWait()
                last_spoke_time = current_milli_time()
                print("Talking")
        else:
            r = requests.get(address+'0')
        # Display the resulting frame
        cv2.imshow('frame',orig_frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
