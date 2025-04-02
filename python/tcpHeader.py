import struct
import socket

def getHeader(packet,start):
    tcp = packet[start:start+20] #포트정보를 위한 4byte 잘라냄

    tcp_arr = struct.unpack('!HHLLBBHHH',tcp) #포트번호 파싱
    
    src = tcp_arr[0]
    dst = tcp_arr[1]#포트정보 파싱
        
    tcp_len = (tcp_arr[4] >> 4) * 4 #상위 4bit(길이정보)를 구하고 * 4 하여 최종 길이 산출 

    return src,dst,start + tcp_len #포트정보 반환