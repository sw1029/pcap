import struct
import socket

def getHeader(packet,start=14):#packet과 시작주소를 같이 받음
    #이더넷 header 다음의 byte부터 파싱
    start_byte = packet[start] #길이를 구하기 위한 첫 번째 바이트
    ip_len = (start_byte % 16) * 4 # % 연산으로 하위 4bit를 구하고 * 4 를 하여 실제 ip header의 바이트 길이를 구함

    ip = packet[start:start + ip_len]#동적으로 잘라냄

    src_raw,dst_raw = struct.unpack('!4s4s',ip[12:20]) #scr, dst 파싱

    src = socket.inet_ntoa(src_raw)
    dst = socket.inet_ntoa(dst_raw) #읽을 수 있게 변환

    return src, dst, start+ip_len #tcp의 시작 idx와 함께 return 