from scapy.all import *

ip = "172.29.95.255"  

pkt = IP(dst=ip)/TCP(dport=12345, sport=54321, flags="PA")/Raw(load="3반 윤서웅(7105) 패킷 전송 테스트입니다.")
send(pkt)