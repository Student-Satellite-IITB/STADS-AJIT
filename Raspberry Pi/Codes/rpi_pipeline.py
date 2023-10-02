from gpiozero import Button
from signal import pause
from picamera import PiCamera
from PIL import Image
from numpy import asarray
import numpy as np
import subprocess


# import filename.py  #Make sure the file is in same directory
# myfile.my_function()  #Calling the function from the file 
def convert_image_to_text(image_array, output_file):
    # Flatten the image array
    #rows,columns=image_array.shape
    flattened_array = image_array.reshape(-1)
    
    with open(output_file, 'w') as file:
        for i, value in enumerate(flattened_array):
            file.write(str(value))
            if i != len(image_array) - 1:
                file.write(',')
            if (i + 1) % 808 == 0:
                file.write('\n')

i=0
def takeImage():
    global i
    i += 1
    print("button_pressed")
    camera1 = PiCamera()
    camera1.resolution = (808, 608)
    camera1.capture('/home/raspi/Desktop/Images/image_pi%s.jpg' % i)
    image1=Image.open('/home/raspi/Desktop/Images/image_pi%s.jpg' % i)
    gray_image1 = image1.convert('L')
    data1=asarray(gray_image1)
    
    file_path1 = '/home/raspi/Desktop/Images/image_pi{}.txt'.format(i)
    convert_image_to_text(data1,file_path1)

    camera1.close()
    print("image_stored")

    camera2 = PiCamera()
    camera2.resolution = (1014, 760)
    camera2.capture('/home/raspi//Desktop/Rpi_Images/image_rpi%s.jpg' % i)
    image2=Image.open('/home/raspi/Desktop/Rpi_Images/image_rpi%s.jpg' % i)
    gray_image2 = image2.convert('L')
    data2=asarray(gray_image2)
    file_path2 = '/home/raspi/Desktop/Rpi_Images/image_rpi{}.txt'.format(i)
    convert_image_to_text(data2,file_path2)
    print("image2_stored")

    camera2.close()
    # data2=asarray(image2)
    # np.savetxt('/home/raspi/Images/image_pi%s.txt', data1, fmt='%d')
    
    
    # Set the command and arguments
    # the file should be present in the same directory
    command = ['python3', 'preprocess_image.py', '-f', '/home/raspi/Desktop/Images/image_pi{}.txt'.format(i) , '-l', '808', '-b', '608', '-i', 'index', '-o', 'image.h']
    subprocess.call(command)

    # Set the path to the C file
    c_file_path = 'main.c'
    # Set the path to the output executable
    executable_path = './exe'
    # Compile the C code
    subprocess.run(['gcc', '-o', 'exe', 'main.c', '-lm'])
    # Execute the compiled C code
    result = subprocess.run(executable_path, stdin = subprocess.PIPE, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    
    # Print the output of the C code
    print("output")
    print(result.stdout)
   

button = Button(2)

button.when_pressed = takeImage

pause()
