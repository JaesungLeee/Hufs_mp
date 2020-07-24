from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import wiringpi as wp
import datetime

app = Flask(__name__)
socketio = SocketIO(app)


SPI_CH = 0
ADC_CH_SOUND = 0
ADC_CS = 29
SPI_SPEED = 500000
wp.wiringPiSetup()
wp.wiringPiSPISetup(SPI_CH, SPI_SPEED)
wp.pinMode(ADC_CS, 1)

#=======================================================================
#				index.html
#=======================================================================
@app.route('/')
def index():
    """Serve the index HTML"""
    return render_template('index.html')


@app.route('/iot_with_flask.js')
def gauge():
    return render_template('iot_with_flask.js')

#=======================================================================
#				socketio ( websocket ) 
#=======================================================================
@socketio.on('measurement_start')
def on_create(data):
    print("measurement_start")
    it=data['iterations']

    # sound.c -> .py
    for i in range(it):
        wp.digitalWrite(ADC_CS, 1)
        buf = bytearray(3)
        buf[0] = 0x06 | ((ADC_CH_SOUND & 0x04)>>2)
        buf[1] = ((ADC_CH_SOUND & 0x03)<<6)
        buf[2] = 0x00
        wp.digitalWrite(ADC_CS,0)
        ret_len, buf = wp.wiringPiSPIDataRW(SPI_CH, bytes(buf))
        buf = bytearray(buf)
        buf[1] = 0x0F & buf[1]
        #value=(buf[1] << 8) | buf[2]
        sound_val = int.from_bytes(bytes(buf), byteorder='big')
        wp.digitalWrite(ADC_CS,1)
        print("sound value=", sound_val)


        now = datetime.datetime.now()
        time_val = now.strftime("%H:%M:%S")

        socketio.sleep(1)  # 1초 sleep
        emit('msg_from_server', {'soundVal': sound_val, 'timdVal' : time_val})

#=======================================================================        
if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5555, debug=False)
