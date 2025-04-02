import struct

def getHeader(packet):
    ether = packet[:12] #~14번째 byte 까지는 이더넷 헤더. type은 필요없으니 12까지만 취함.
    dst,src = struct.unpack('!6s6s',ether)#6byte + 6byte => 총 12byte 파싱
    return dst,src

