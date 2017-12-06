'use strict'

const Access = use ('App/Models/Access')
const User = use ('App/Models/User')

class AccessController {
  async index ({response, request}) {
    const accesses = await Access.query().with('user').fetch()
    response.send(accesses)
  }

  async store ({response, request}) {
    const input = request.only(['rfid', 'date'])
    const user = await User.query().where('rfid', input.rfid).first()
    // console.log(input)
    if(user) {
      user.accesses().create({'date': input.date})
      response.status(200)
      response.send({'return': '1'})
    } else {
      response.status(404)
      response.send({'return': '0'})
    }
  }
}

module.exports = AccessController
