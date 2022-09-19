import sys
import json
import requests
import time
import datetime

headers={'Content-Type': 'application/json'}
url = 'http://harvest.soracom.io'

def main():
    interval_sec = 5 

    payload = {}
    payload['device_id'] = 'test'
    payload['timestamp'] = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    while(True):
        start_time = time.time()
        
        print('Data sending ...')
        
        try:
            request = requests.post(url, data=json.dumps(payload), headers=headers, timeout=5)
            print(request)
        except requests.exceptions.ConnectTimeout:
            print('ERROR: 接続がタイムアウトしました。"connect_air.sh" は実行していますか？')
            if request.status_code == 400:
                print('ERROR: データ送信に失敗しました。Harvest が有効になっていない可能性があります。')
        
        wait_time = start_time + interval_sec - start_time
        if wait_time > 0:
            time.sleep(wait_time)
            
if __name__ == '__main__':
    main()