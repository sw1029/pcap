'''
코드 리뷰 시에 기능별로 분리하여 코드를 짜는 것이 
가시성이 더 나을 것 같아 분리하여 작성합니다.
'''

from python import ethernetHeader, message, ipHeader
import tcpHeader

import pcapy
import binascii

device = pcapy.findalldevs()[0] #eth0 사용
cap = pcapy.open_live(device, 65536, 1, 100) 
#pcapy로 device 가져옴. 100ms 단위로 들어오는 패킷 감지
cap.setfilter('tcp')

_ , packet = cap.next() #패킷이 들어올 때 까지 무한 대기
    
dst_mac,src_mac = ethernetHeader.getHeader(packet)
src_ip,dst_ip,tcp_idx = ipHeader.getHeader(packet, 14)
src_port,dst_port,msg_idx = tcpHeader.getHeader(packet, tcp_idx)
msg = message.getMsg(packet, msg_idx)

print(f"src_mac = {binascii.hexlify(src_mac).decode('utf-8')}")
print(f"dst_mac = {binascii.hexlify(dst_mac).decode('utf-8')}") #binascii로 16진수 변환

print(f"src_ip = {src_ip}")
print(f"dst_ip = {dst_ip}")

print(f"src_port = {src_port}")
print(f"dst_port = {dst_port}")

print(f"msg = {msg.decode('utf-8')}")