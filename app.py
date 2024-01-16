import jinja2
from aiohttp import web
import aiohttp_jinja2 #med de her pis imports
from twilio.rest import Client
import json

with open("credentials.json") as f:
    data = json.load(f)
    credentials = data

client = Client(credentials["account_sid"], credentials["auth_token"])



routes = web.RouteTableDef()


app = web.Application()
app.add_routes([web.static('/', './')])

aiohttp_jinja2.setup(app, 
    loader=jinja2.FileSystemLoader('/path/to/templates/folder')) #få det her lort til at virke

@routes.post('/send_message')
async def send_message(request):
    message = client.messages.create(
        from_='+12057782407',
        to='+4541423758',
        body="Din potteplante er løbet tør for vand",
    )
    print('send message to {0}'.format(message.sid))
    return web.Response(text="OK")


routes.static('/', './')
app.add_routes(routes)

web.run_app(app)
