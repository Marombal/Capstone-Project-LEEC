#
# This example shows off how to find circles in the image using the Hough
# Transform. https://en.wikipedia.org/wiki/Circle_Hough_Transform
#
# Note that the find_circles() method will only find circles which are completely
# inside of the image. Circles which go outside of the image/roi are ignored...

import sensor, image, time,pyb,math,ustruct
from pyb import Pin

text = "Hello          \0World!         \0"
data = ustruct.pack("<bi%ds" % len(text), 85, len(text), text) # 85 is a sync char.

spi = pyb.SPI(2, pyb.SPI.SLAVE, polarity=0, phase=0)

# NSS callback.
def nss_callback(line):
    global spi, data
    try:
        print("entrou")
        spi.send(data, timeout=1000)
    except OSError as err:
        print("ola")
        pass # Don't care about errors - so pass.
             # Note that there are 3 possible errors. A timeout error, a general purpose error, or
             # a busy error. The error codes are 116, 5, 16 respectively for "err.arg[0]".
# Configure NSS/CS in IRQ mode to send data when requested by the master.
pyb.ExtInt(pyb.Pin("P3"), pyb.ExtInt.IRQ_FALLING, pyb.Pin.PULL_UP, nss_callback)

count_ret=0
count_tri=0
count_est=0
count_circ=0
count_est_verde=0
count_ret_verde=0
count_tri_verde=0
count_circ_verde=0
count_est_azul=0
count_ret_azul=0
count_tri_azul=0
count_circ_azul=0
flag=0
flag_tapete=1
time_end=0
time_init=0
p_out = Pin('P7', Pin.OUT_PP)
p_out.high()
sensor.reset()
sensor.set_pixformat(sensor.RGB565) # grayscale is faster
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
clock = time.clock()
count=0
led1 = pyb.LED(1)
led2 = pyb.LED(2)
led3 = pyb.LED(3)
led1.on()
led2.on()
led3.on()
verif=0
x=10
y=255

thresholdsVermelho = (100, 0, 100, 15, 127, -39)
thresholdsVerde = (0, 67, -128, 26, 73, -21)
thresholdsBranco = (100, 30, -70, 98, 9, -13)
while(True):
    print("CONTADORES VERMELHO: ",count_tri,count_ret,count_est,count_circ)
    print("CONTADORES VERDE: ",count_tri_verde,count_ret_verde,count_est_verde,count_circ_verde)
    print("CONTADORES AZUL: ",count_tri_azul,count_ret_azul,count_est_azul,count_circ_azul)
    clock.tick()
    #img = sensor.snapshot().lens_corr(0)
    img = sensor.snapshot() # Takes a snapshot and saves it in memory

    # Find blobs with a minimal area of 50x50 = 2500 px
    # Overlapping blobs will be merged
    blobs = img.find_blobs([thresholdsVermelho,thresholdsVerde,thresholdsBranco], area_threshold=2500, merge=True)
    # Draw blobs
    for blob in blobs:
        print("blob code: ",blob.code())
        # Draw a rectangle where the blob was found
        '''if(blob.code() == 4): #Vermelho
            print("amarelo")'''
        if(blob.code() == 5 or blob.code()==7 or blob.code()==1): #Vermelho
            print("VERMELHO")
            #print("flag tapete",flag_tapete)
            if(flag_tapete==1):
                flag_tapete=0
                pyb.delay(1000)
                p_out.low()

            for r in img.find_rects(threshold = 45000):
                p_medio_x=0
                p_medio_y=0
                #img.draw_rectangle(r.rect(), color = (255, 0, 0))
                for p in r.corners():
                    #img.draw_circle(p[0], p[1], 5, color = (0, 255, 0))
                    p_medio_x+=p[0]
                    p_medio_y+=p[1]
                p_medio=[p_medio_x/4,p_medio_y/4]
                #img.draw_cross(int(p_medio[0]),int(p_medio[1]), color=(0,255,0))

                color_center=img.get_pixel(int(p_medio[0]),int(p_medio[1])) #color_center tem RGB do centroide
                #img.draw_circle(blob.cx(),blob.cy(),5,color = (0, 255, 0))
                print("cor: ")
                print(color_center)
                if (color_center[0]>130 and color_center[1]>10 and color_center[2]<100): #pormenores de limites
                    if(count_ret==0):
                        time_init=time.time()
                        print(time_init)
                    if(count_ret==9):
                        time_end=time.time()
                        print(time_end)
                    count_ret=count_ret+1
                    print("detecao : ",count_ret)

                    print("retangulo vermelho",count_ret)
                    break
                #else: print("erro")
            #CIRCULO
            for c in img.find_circles(threshold = 3200, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 20, r_max = 100, r_step = 2):
                img.draw_circle(c.x(), c.y(), c.r(), color = (255, 0, 0))
                color_center=img.get_pixel(c.x(),c.y())
                print(color_center)
                if (color_center[0]>130 and color_center[1]<100 and color_center[2]<100):
                    print("detecao : ",count_circ)
                    if(count_circ==0): time_init=time.time()
                    if(count_circ==9): time_end=time.time()
                    print("time",clock.fps())
                    print("circulo vermelho")
                    count_circ=count_circ+1
                    break
            #TRIANGULO

            l=img.find_lines(threshold=1500)
            lista=[]
            for lines in l:
                img.draw_line(lines.line(),color=(255,0,0))
                #print(lines.theta())
                lista.append(lines.theta())
                #img.draw_circle(lines.x1(),lines.y1(),5,color = (0, 255, 0))
                #img.draw_circle(lines.x2(),lines.y2(),5,color = (0, 255, 0))

            angles=[]
            if(len(lista)>=3):
                lista2=sorted(lista)
                #print("angulos retas: ",lista2)
                for i in range(len(lista)-1):
                    angles.append(lista2[i+1]-lista2[i])
                angles.append(180-lista2[len(lista)-1]+lista2[0])
                count=0
                for i in range(len(lista)):
                    print(angles[i])
                    if(50<=angles[i]<=70):
                        count=count+1
                if(count==3):
                    if(count_tri==0):
                        time_init=clock.fps()
                        print(time_init)
                    if(count_tri==9):
                        time_end=clock.fps()
                        print(time_end)
                    count_tri=count_tri+1
                    print("Triangulo Vermelho",count_tri)

            #ESTRELA
            l=img.find_lines(threshold=1000)
            lista=[]
            count=0
            for lines in l:
                img.draw_line(lines.line(),color=(x,y,0))
                #print(lines.theta())
                lista.append(lines.theta())
                if(count==0):
                    img.draw_line(lines.line(),color=(255,0,0))
                elif(count==1):
                    img.draw_line(lines.line(),color=(0,255,0))
                elif(count==2):
                    img.draw_line(lines.line(),color=(0,0,255))
                elif(count==3):
                    img.draw_line(lines.line(),color=(255,255,0))
                elif(count==4):
                    img.draw_line(lines.line(),color=(255,0,255))
                count+=1
            angles=[]
            print("LISTA:", len(lista))
            if(len(lista)>=5):
                lista2=sorted(lista)
                #print("angulos retas: ",lista2)
                for i in range(len(lista)-1):
                    angles.append(lista2[i+1]-lista2[i])
                angles.append(180-lista2[len(lista)-1]+lista2[0])
                print("angulos internos: ", angles)
                #sum =0
                #for i in range(5):
                #    sum=sum+angles[i]
                #print("SOMA DOS ANGULOS INTERNOS: ",sum)
                count=0
                for i in range(len(lista)):
                    if(25<=angles[i]<=50):
                        count=count+1
                if(count==5):
                    if(count_est==0): time_init=clock.fps()
                    if(count_est==9): time_end=cloc.fps()
                    count_est=count_est+1
                    print("Estrela Vermelha")
                    break


        elif(blob.code()==6): #Verde
            #RETANGULO
            print("VERDE")
            if(flag_tapete==1):
                flag_tapete=0
                pyb.delay(1000)
                p_out.low()
            for r in img.find_rects(threshold = 45000):
                #img.draw_rectangle(r.rect(), color = (255, 0, 0))
                p_medio_x=0
                p_medio_y=0
                for p in r.corners():
                    #img.draw_circle(p[0], p[1], 5, color = (0, 255, 0))
                    p_medio_x+=p[0]
                    p_medio_y+=p[1]
                p_medio=[p_medio_x/4,p_medio_y/4]
                color_center=img.get_pixel(int(p_medio[0]),int(p_medio[1]))
                print(color_center)
                if (color_center[0]<100 and color_center[1]>90 and color_center[2]<100):
                    count_ret_verde=count_ret_verde+1
                    print("retangulo verde")
                    break
            #CIRCULO
            for c in img.find_circles(threshold = 6000, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 20, r_max = 100, r_step = 2):
                img.draw_circle(c.x(), c.y(), c.r(), color = (255, 0, 0))
                color_center=img.get_pixel(c.x(),c.y())
                print("circulo verde:");
                print(color_center)
                if (color_center[0]<100 and color_center[1]>10 and color_center[2]<100):
                    count_circ_verde=count_circ_verde+1
                    print("circulo verde")
                    break
            #TRIANGULO

            l=img.find_lines(threshold=1500)
            lista=[]
            for lines in l:
                img.draw_line(lines.line(),color=(255,0,0))
                #print(lines.theta())
                lista.append(lines.theta())
            angles=[]
            if(len(lista)>=3):
                lista2=sorted(lista)
                #print("angulos retas: ",lista2)
                for i in range(len(lista)-1):
                    angles.append(lista2[i+1]-lista2[i])
                angles.append(180-lista2[len(lista)-1]+lista2[0])
                count=0
                for i in range(len(lista)):
                    print(angles[i])
                    if(50<=angles[i]<=70):
                        count=count+1
                if(count==3):
                    count_tri_verde=count_tri_verde+1
                    print("Triangulo Verde",count_tri_verde)
            #ESTRELA
            l=img.find_lines(threshold=1000)
            lista=[]
            count=0
            print("ESTRELA tamanho linhas:",len(l))
            for lines in l:
                img.draw_line(lines.line(),color=(x,y,0))
                #print(lines.theta())
                lista.append(lines.theta())
                if(count==0):
                    img.draw_line(lines.line(),color=(255,0,0))
                '''elif(count==1):
                    img.draw_line(lines.line(),color=(0,255,0))
                elif(count==2):
                    img.draw_line(lines.line(),color=(0,0,255))
                elif(count==3):
                    img.draw_line(lines.line(),color=(255,255,0))
                elif(count==4):
                    img.draw_line(lines.line(),color=(255,0,255))'''
                count+=1
            angles=[]
            print("tamanho:",len(lista))
            if(len(lista)>=5):
                lista2=sorted(lista)
                #print("angulos retas: ",lista2)
                for i in range(len(lista)-1):
                    angles.append(lista2[i+1]-lista2[i])
                angles.append(180-lista2[4]+lista2[0])
                print("angulos internos: ", angles)
                #sum =0
                #for i in range(5):
                #    sum=sum+angles[i]
                #print("SOMA DOS ANGULOS INTERNOS: ",sum)
                count=0
                for i in range(len(lista)):
                    if(30<=angles[i]<=45):
                        count=count+1
                if(count==5):
                    count_est_verde=count_est_verde+1
                    print("Estrela Verde")
                    break

        '''if(blob.code() == 4): #Vermelho
            print("amarelo")
            p_out.low()
            print("branco")
            flag_tapete=0
            print("AZUL")
            for r in img.find_rects(threshold = 45000):
                p_medio_x=0
                p_medio_y=0
                #img.draw_rectangle(r.rect(), color = (255, 0, 0))
                for p in r.corners():
                    #img.draw_circle(p[0], p[1], 5, color = (0, 255, 0))
                    p_medio_x+=p[0]
                    p_medio_y+=p[1]
                p_medio=[p_medio_x/4,p_medio_y/4]
                #img.draw_cross(int(p_medio[0]),int(p_medio[1]), color=(0,255,0))

                color_center=img.get_pixel(int(p_medio[0]),int(p_medio[1])) #color_center tem RGB do centroide
                #img.draw_circle(blob.cx(),blob.cy(),5,color = (0, 255, 0))
                print("cor: ")
                print(color_center)
                if (color_center[0]<100 and color_center[1]>50 and color_center[2]>160): #pormenores de limites
                    count_ret_azul=count_ret_azul+1
                    print("retangulo azul",count_ret_azul)
                    break
                #else: print("erro")
            #CIRCULO
            for c in img.find_circles(threshold = 3200, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 20, r_max = 100, r_step = 2):
                img.draw_circle(c.x(), c.y(), c.r(), color = (255, 0, 0))
                color_center=img.get_pixel(c.x(),c.y())
                print(color_center)
                if (color_center[0]<100 and color_center[1]>30 and color_center[2]>160):
                    print("circulo azul")
                    count_circ_azul=count_circ_azul+1
                    break
            #TRIANGULO

            l=img.find_lines(threshold=1500)
            lista=[]
            for lines in l:
                img.draw_line(lines.line(),color=(255,0,0))
                #print(lines.theta())
                lista.append(lines.theta())
                #img.draw_circle(lines.x1(),lines.y1(),5,color = (0, 255, 0))
                #img.draw_circle(lines.x2(),lines.y2(),5,color = (0, 255, 0))

            angles=[]
            if(len(lista)>=3):
                lista2=sorted(lista)
                #print("angulos retas: ",lista2)
                for i in range(len(lista)-1):
                    angles.append(lista2[i+1]-lista2[i])
                angles.append(180-lista2[len(lista)-1]+lista2[0])
                count=0
                for i in range(len(lista)):
                    print(angles[i])
                    if(50<=angles[i]<=70):
                        count=count+1
                if(count==3):
                    count_tri_azul=count_tri_azul+1
                    print("Triangulo Azul",count_tri_azul)

            #ESTRELA
            l=img.find_lines(threshold=1000)
            lista=[]
            count=0
            for lines in l:
                img.draw_line(lines.line(),color=(x,y,0))
                #print(lines.theta())
                lista.append(lines.theta())
                if(count==0):
                    img.draw_line(lines.line(),color=(255,0,0))
                elif(count==1):
                    img.draw_line(lines.line(),color=(0,255,0))
                elif(count==2):
                    img.draw_line(lines.line(),color=(0,0,255))
                elif(count==3):
                    img.draw_line(lines.line(),color=(255,255,0))
                elif(count==4):
                    img.draw_line(lines.line(),color=(255,0,255))
                count+=1
            angles=[]
            #print("LISTA:", len(lista))
            if(len(lista)>=5):
                lista2=sorted(lista)
                #print("angulos retas: ",lista2)
                for i in range(len(lista)-1):
                    angles.append(lista2[i+1]-lista2[i])
                angles.append(180-lista2[len(lista)-1]+lista2[0])
                print("angulos internos: ", angles)
                #sum =0
                #for i in range(5):
                #    sum=sum+angles[i]
                #print("SOMA DOS ANGULOS INTERNOS: ",sum)
                count=0
                for i in range(len(lista)):
                    if(30<=angles[i]<=45):
                        count=count+1
                if(count==5):
                    count_est_azul=count_est_azul+1
                    print("Estrela Azul", verif)
                    break'''



    # Verification
    # str_obj must be a 32 bytes string. 16bytes(form) + 16bytes(colour)
    verif = 10
    if(count_ret>=verif):
        flag = 1
        str_obj = "RETANGULO      \0VERMELHO       \0"
        ###########01234567890123456789012345678901
    elif(count_tri>=verif):
        flag = 1
        str_obj = "TRIANGULO      \0VERMELHO       \0"
    elif(count_est>=verif/2):
        flag = 1
        str_obj = "ESTRELA        \0VERMELHO       \0"
    elif(count_circ>=verif):
        flag = 1
        str_obj = "CIRCULO        \0VERMELHO       \0"
    elif(count_est_verde>=verif/2):
        flag = 1
        str_obj = "ESTRELA        \0VERDE          \0"
    elif(count_ret_verde>=verif):
        flag = 1
        str_obj = "RETANGULO      \0VERDE          \0"
    elif(count_tri_verde>=verif):
        flag = 1
        str_obj = "TRIANGULO      \0VERDE          \0"
    elif(count_circ_verde>=verif):
        flag=1
        str_obj = "CIRCULO        \0VERDE          \0"
    elif(count_est_azul>=verif):
        flag = 1
        str_obj = "ESTRELA        \0AZUL           \0"
    elif(count_ret_azul>=verif):
        flag = 1
        str_obj = "RETANGULO      \0AZUL           \0"
    elif(count_tri_azul>=verif):
        flag = 1
        str_obj = "TRIANGULO      \0AZUL           \0"
    elif(count_circ_azul>=verif):
        flag=1
        str_obj = "CIRCULO        \0AZUL           \0"

    if(flag == 1):
        # Reset both flag and counters
        #print("entrou")
        print(str_obj)
        flag = 0
        count_ret=0
        count_tri=0
        count_est=0
        count_circ=0
        count_est_verde=0
        count_ret_verde=0
        count_tri_verde=0
        count_circ_verde=0
        count_est_azul=0
        count_ret_azul=0
        count_tri_azul=0
        count_circ_azul=0
        #....

        #Envia
        text = str_obj
        #text = "Hello           World.          "
        data = ustruct.pack("<bi%ds" % len(text), 85, len(text), text) # 85 is a sync char.

        pyb.delay(10000)
        p_out.high()
        flag_tapete=1


        text = "Hello          \0World!         \0"
        data = ustruct.pack("<bi%ds" % len(text), 85, len(text), text) # 85 is a sync char.


        pyb.delay(7000)
        p_out.low()
        pyb.delay(2000)
        p_out.high()


