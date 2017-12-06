'use strict'

const Schema = use('Schema')

class UserSchema extends Schema {
  up () {
    this.create('users', table => {
      table.increments()
      table.string('name', 80).notNullable()
      table.string('category', 254).notNullable()
      table.string('rfid', 60).notNullable().unique()
      table.timestamps()
    })
  }

  down () {
    this.drop('users')
  }
}

module.exports = UserSchema
