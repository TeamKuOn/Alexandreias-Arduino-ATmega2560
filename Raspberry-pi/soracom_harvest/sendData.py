import sys
import json
import requests
import time

json_data = {"clock/10M": clock_n, "temp": temp_n}
encode_json_data = json.dumps(json_data)

requests.post('http://harvest.soracom.io', data=encode_json_data, headers={'Content-Type': 'application/json'})