from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import wiringpi as wp
import datetime

app = Flask(__name__)
socketio = SocketIO(app)

// wiringPi 코드
LED_PIN = 7
SPI_CH = 0
ADC_CH_LIGHT = 0
ADC_CS = 29
SPI_SPEED = 500000
wp.wiringPiSetup() 
wp.wiringPiSPISetup(SPI_CH, SPI_SPEED)
wp.pinMode(LED_PIN, 1)
wp.pinMode(ADC_CS, 1)  // light 센서를 쓰기 위한 pinMode

#=======================================================================
#               index.html
#=======================================================================
@app.route('/')  // / 디렉토리 접근 하면 index 함수 불림
def index():
    """Serve the index HTML"""
    return render_template('index.html')

#=======================================================================
#               led action + response
#=======================================================================
@app.route("/led1/<led_state>")  // /led1/<led_state> 로 접근하면 밑에 함수 불림
def control_led_action(led_state):
    print("control_led_action")
    
    if led_state == "true": 
        print("action==true")
        wp.digitalWrite(LED_PIN, 1)
        ledS="ON"      
    else: 
        print("action==false")
        wp.digitalWrite(LED_PIN, 0)
        ledS="OFF"
      
    now = datetime.datetime.now()
    timeString = now.strftime("%Y-%m-%d %H:%M:%S")
    templateData = {
      'time': timeString ,
      'ledS' : ledS
    }                  
    return render_template('ajax_led_response.html',**templateData)




@app.route('/iot_with_flask.js')  // index.html에서 js 파일을 부르기 위해 함
def gauge():  
    return render_template('iot_with_flask.js')  

#=======================================================================
#               socketio ( websocket ) 
#=======================================================================
@socketio.on('measurement_start')
def on_create(data):
    print("measurement_start")
    it=data['iterations']
    for i in range(it):
        wp.digitalWrite(ADC_CS, 1)
        buf = bytearray(3)
        buf[0] = 0x06 | ((ADC_CH_LIGHT & 0x04)>>2)
        buf[1] = ((ADC_CH_LIGHT & 0x03)<<6)
        buf[2] = 0x00
        wp.digitalWrite(ADC_CS,0)
        ret_len, buf = wp.wiringPiSPIDataRW(SPI_CH, bytes(buf))
        buf = bytearray(buf)
        buf[1] = 0x0F & buf[1]
        #value=(buf[1] << 8) | buf[2]
        light_val = int.from_bytes(bytes(buf), byteorder='big')
        wp.digitalWrite(ADC_CS,1)
        print("light value=", light_val)
        socketio.sleep(.2)
        emit('msg_from_server', {'lightVal': light_val})

#=======================================================================        
if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5555, debug=False)

