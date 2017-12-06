'use strict'

const Guest = use ('App/Models/Guest')

class GuestController {
  async index ({response, request}) {
    const guests = await Guest.query().fetch()
    response.send(guests)
  }

  async store ({response, request}) {
    const input = request.only(['date', 'im_name'])
    const guest = await Guest.create(input)
  }

}

module.exports = GuestController
