# -*- coding: utf-8 -*- 
from coapthon.server.coap import CoAP
import time
import sys
from coapthon.resources.resource import Resource

#RFID resource
class RFIDResource(Resource):
    def __init__(self, name="RFID"):
        super(RFIDResource, self).__init__(name)
        self.payload = "RFID resource"

    def render_GET_advanced(self, request, response):
        return self, response, self.render_GET_separate

    def render_POST_advanced(self, request, response):
        return self, response, self.render_POST_separate

    def render_PUT_advanced(self, request, response):
        return self, response, self.render_PUT_separate

    def render_DELETE_advanced(self, request, response):
        return self, response, self.render_DELETE_separate

    def render_GET_separate(self, request, response):
        time.sleep(5)
        response.payload = self.payload
        response.max_age = 20
        return self, response

    def render_POST_separate(self, request, response):
        self.payload = request.payload
        response.payload = "Response changed through POST"
        return self, response

    def render_PUT_separate(self, request, response):
		self.payload = request.payload
		#check RFID
		if request.payload == '192.227.68.26':
			response.payload = '1'
		else:
			response.payload = '0'
		return self, response

    def render_DELETE_separate(self, request, response):
        response.payload = "Response deleted"
        return True, response


#Camera resource

class CoAPServer(CoAP):
	def __init__(self, host, port):
		CoAP.__init__(self, (host, port))
		self.add_resource('rfid/', RFIDResource())
		print "Servidor iniciado em coap://"+host+":"+str(port)

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
		print "Desligando servidor..."
		server.close()
		print "Servidor terminado."

main()


