'use strict'

const Schema = use('Schema')

class AccessSchema extends Schema {
  up () {
    this.create('accesses', (table) => {
      table.increments()
      table.integer('user_id').unsigned().references('id').inTable('users').notNullable()
      table.string('date').notNullable()
      table.timestamps()
    })
  }

  down () {
    this.drop('accesses')
  }
}

module.exports = AccessSchema
