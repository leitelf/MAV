'use strict'

/*
|--------------------------------------------------------------------------
| Routes
|--------------------------------------------------------------------------
|
| Http routes are entry points to your web application. You can create
| routes for different URL's and bind Controller actions to them.
|
| A complete guide on routing is available here.
| http://adonisjs.com/guides/routing
|
*/

const Route = use('Route')

Route.get('/', ({ request }) => {
  return { greeting: 'MAV Project!' }
})

Route.get('/users', 'UserController.index')
Route.post('/users', 'UserController.store')
Route.put('/check', 'UserController.check')

Route.get('/accesses', 'AccessController.index')
Route.post('/accesses', 'AccessController.store')

Route.get('/guests', 'GuestController.index')
Route.post('/guests', 'GuestController.store')
