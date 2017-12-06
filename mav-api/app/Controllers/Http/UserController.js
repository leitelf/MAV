'use strict'
const User = use ('App/Models/User')
class UserController {

  async store ({response, request}) {
    const input = request.only(['name', 'rfid', 'category'])

    const user = await User.create(input)
  }

  async index ({response, request}) {
    const users = await User.query().with('accesses').fetch()
    response.send(users)
  }

  async check ({response, request}) {
    const input = request.only(['rfid'])

    const user = await User.query().where('rfid', input.rfid).first()

    if (user) {
      response.status(200)
      response.send({'return': '1'})
    } else {
      response.status(404)
      response.send({'return': '0'})
    }
  }
}

module.exports = UserController
