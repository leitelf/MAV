from coapthon.resources.resource import Resource

class PLATEResource(Resource):

	def __init__(self, name="RFIDResource"):
		super(RFIDResource, self).__init__(name)
		self.payload = "RFID"
	

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
		#salvar entrada
		allowed = False
		#se encontrado
		if (allowed) :
			response.payload = "1"
		else :
			response.payload = "0"
		return self, response

	def render_DELETE_separate(self, request, response):
		response.payload = "Response deleted"
		return True, response

class RFIDResource(Resource):

	def __init__(self, name="RFIDResource"):
		super(RFIDResource, self).__init__(name)
		self.payload = "RFID"
	

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
		#salvar entrada
		#consultar banco de dados
		allowed = False
		#se encontrado
		if (allowed) :
			response.payload = "1"
		else :
			response.payload = "0"
		return self, response

	def render_DELETE_separate(self, request, response):
		response.payload = "Response deleted"
		return True, response
