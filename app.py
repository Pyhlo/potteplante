import jinja2
import aiohttp_jinja2 #med de her pis imports

#from aiohttp import web


routes = web.RouteTableDef()

aiohttp_jinja2.setup(app, 
    loader=jinja2.FileSystemLoader('/path/to/templates/folder')) #få det her lort til at virke

@routes.post('/send_message')
async def send_message(request):
    print("")
    return web.Response(text="OK")

app = web.Application()
app.add_routes([web.static('/', './')])

routes.static('/', './')
app.add_routes(routes)

web.run_app(app)
