'use strict'

const Model = use('Model')

class User extends Model {

  accesses () {
    return this.hasMany('App/Models/Access')
  }

}

module.exports = User
