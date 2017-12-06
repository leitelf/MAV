'use strict'

const Model = use('Model')

class Access extends Model {
  user () {
    return this.belongsTo('App/Models/User')
  }
}

module.exports = Access
