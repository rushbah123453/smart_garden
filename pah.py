import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO
import time


#define variables
MQTT_HOST="192.168.43.89"
#MQTT_HOST="192.168.100.2"
MQTT_PORT=1883
MQTT_KEEP_ALIVE=5
MQTT_TOPIC="/led/ro"

# Define event callbacks
def on_connect(mosq, obj, rc):
#print("rc: " + str(rc))
    mqttc.subscribe(MQTT_TOPIC,0)

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_message(mosq, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    if(str(msg.payload)=="ON1"):
       GPIO.setmode(GPIO.BOARD)
       GPIO.setup(12,GPIO.OUT)
       GPIO.output(12,1)
       #while((str(msg.payload)!="ON2")):
       GPIO.output(12,0)
       time.sleep(6)
       GPIO.output(12,1)
       GPIO.cleanup() 
    if(str(msg.payload)=="ON2"):
       GPIO.setmode(GPIO.BOARD)
       GPIO.setup(16,GPIO.OUT)
       GPIO.output(16,1)
       GPIO.output(16,0)
       time.sleep(6)
       GPIO.output(16,1)
       GPIO.cleanup()

#def on_publish(mosq, obj, mid):
#    print("mid: " + str(mid))



#def on_log(mosq, obj, level, string):
#    print(string)

mqttc = mqtt.Client()
# Assign event callbacks
mqttc.on_message = on_message
mqttc.on_connect = on_connect
#mqttc.on_publish = on_publish
mqttc.on_subscribe = on_subscribe

mqttc.connect(MQTT_HOST,MQTT_PORT,MQTT_KEEP_ALIVE)
mqttc.loop_forever()
# Uncomment to enable debug messages
#mqttc.on_log = on_log

# Parse CLOUDMQTT_URL (or fallback to localhost)
url_str = os.environ.get('www.cloudmqtt.com', 'mqtt://192.168.1.4:1883')
url = urlparse.urlparse(url_str)

# Connect
mqttc.username_pw_set(url.kziuqczj, url.TA8RdktQeUJV)
mqttc.connect(url.m11.cloudmqtt.com,12297)

# Start subscribe, with QoS level 0
mqttc.subscribe("hello/world", 0)

# Publish a message
#mqttc.publish("hello/world", "my message")

# Continue the network loop, exit when an error occurs
#rc = 0
#while rc == 0:
#    rc = mqttc.loop()
#print("rc: " + str(rc))
