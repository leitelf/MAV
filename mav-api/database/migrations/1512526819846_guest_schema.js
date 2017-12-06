'use strict'

const Schema = use('Schema')

class GuestSchema extends Schema {
  up () {
    this.create('guests', (table) => {
      table.increments()
      table.string('im_name').notNullable().unique()
      table.string('date').notNullable()
      table.timestamps()
    })
  }

  down () {
    this.drop('guests')
  }
}

module.exports = GuestSchema
