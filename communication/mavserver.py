# -*- coding: utf-8 -*-
from coapthon.server.coap import CoAP
from mavresources import RFIDResource
import sys
import os

class CoAPServer(CoAP):
    def __init__(self, host, port):
        CoAP.__init__(self, (host, port))
        self.add_resource('rfid/', RFIDResource())
	print("Servidor iniciado em coap://"+host+":"+ str(port))


def main():
	argc = len(sys.argv)

	if argc != 3:
		print("Esse script funciona com 2 argumentos: <host> <port>")
		print("<host>: endereço IP do servidor")
		print("<port>: porta do servidor")
		exit(1)

	host = sys.argv[1]
	port = int(sys.argv[2])

	server = CoAPServer(host, port)
	try:
		server.listen(10)
	except KeyboardInterrupt:
		print "Desligando servidor"
		server.close()
		print "Saindo..."

# script
main()
