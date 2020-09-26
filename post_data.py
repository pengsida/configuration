import requests
import json
import re
from datetime import datetime, timedelta
import hashlib
from urllib import parse
from apscheduler.schedulers.blocking import BlockingScheduler

app_key = '8fceb735082b5a529312040b58ea780b'
sign_code = 'c640ca392cd45fb3a55b00a63a86c618'


def _rsa_encrypt(password_str, e_str, M_str):
    password_bytes = bytes(password_str, 'ascii')
    password_int = int.from_bytes(password_bytes, 'big')
    e_int = int(e_str, 16)
    M_int = int(M_str, 16)
    result_int = pow(password_int, e_int, M_int)
    return hex(result_int)[2:].rjust(128, '0')


def get_login_sign(timestamp):
    k = sign_code + '/api/login'
    k = k + timestamp + ' ' + sign_code
    sign = hashlib.md5(k.encode()).hexdigest()
    return sign


def get_rolelogin_sign(timestamp):
    k = sign_code + '/roleLoginroleid3'
    k = k + timestamp + ' ' + sign_code
    sign = hashlib.md5(k.encode()).hexdigest()
    return sign


def get_reservation_sign(timestamp):
    k = sign_code + '/api/protocols/code/RESERVATION_PROTOCOLnocache' + timestamp
    k = k + timestamp + ' ' + sign_code
    sign = hashlib.md5(k.encode()).hexdigest()
    return sign


def get_info_sign(timestamp):
    k = sign_code + '/api/reservation/campus/venue/infoisApp0nocache' + timestamp
    k = k + timestamp + ' ' + sign_code
    sign = hashlib.md5(k.encode()).hexdigest()
    return sign


def get_timeid_sign(timestamp, day):
    k = sign_code + '/api/reservation/day/infonocache' + timestamp + 'searchDate' + day + 'venueSiteId23'
    k = k + timestamp + ' ' + sign_code
    sign = hashlib.md5(k.encode()).hexdigest()
    return sign


def get_order_sign(timestamp, data):
    isOfflineTicket = 'isOfflineTicket' + data['isOfflineTicket']
    reservationDate = 'reservationDate' + data['reservationDate']
    reservationOrderJson = 'reservationOrderJson' + data['reservationOrderJson']
    venueSiteId = 'venueSiteId' + data['venueSiteId']
    weekStartDate = 'weekStartDate' + data['weekStartDate']
    data = ''.join([
        isOfflineTicket, reservationDate, reservationOrderJson, venueSiteId,
        weekStartDate
    ])
    k = sign_code + '/api/reservation/order/info' + data + timestamp + ' ' + sign_code
    sign = hashlib.md5(k.encode()).hexdigest()
    return sign


def get_submit_sign(timestamp, data):
    buddyIds = 'buddyIds' + data['buddyIds']
    isOfflineTicket = 'isOfflineTicket' + data['isOfflineTicket']
    phone = 'phone' + data['phone']
    reservationDate = 'reservationDate' + data['reservationDate']
    reservationOrderJson = 'reservationOrderJson' + data['reservationOrderJson']
    venueSiteId = 'venueSiteId' + data['venueSiteId']
    weekStartDate = 'weekStartDate' + data['weekStartDate']
    data = ''.join([
        buddyIds, isOfflineTicket, phone, reservationDate,
        reservationOrderJson, venueSiteId, weekStartDate
    ])
    k = sign_code + '/api/reservation/order/submit' + data + timestamp + ' ' + sign_code
    sign = hashlib.md5(k.encode()).hexdigest()
    return sign


def get_pay_sign(timestamp, tradeNo):
    k = sign_code + '/api/venue/finances/order/payvenueTradeNo' + tradeNo
    k = k + timestamp + ' ' + sign_code
    sign = hashlib.md5(k.encode()).hexdigest()
    return sign


def order(username, password):
    login_url = "https://zjuam.zju.edu.cn/cas/login?service=http://www.tyys.zju.edu.cn/venue-server/sso/manageLogin"

    sess = requests.Session()
    res = sess.get(login_url)
    execution = re.search('name="execution" value="(.*?)"', res.text).group(1)
    res = sess.get(url='https://zjuam.zju.edu.cn/cas/v2/getPubKey').json()
    n, e = res['modulus'], res['exponent']
    encrypt_password = _rsa_encrypt(password, e, n)

    data = {
        'username': username,
        'password': encrypt_password,
        'execution': execution,
        '_eventId': 'submit'
    }
    res = sess.post(url=login_url, data=data)

    cookies = sess.cookies.get_dict()
    JSESSIONID = 'JSESSIONID=' + cookies['JSESSIONID'] + ';'
    _ga = '_ga=' + 'GA1.3.2084284265.1599723003' + ';'
    wsess = 'wsess=' + 'iatgrjuvk52q7r9ioq5mcbbq61' + ';'
    sudy_ck = 'sudy_ck=' + '9C24CC3C6410F3C00193109B09906184BB15EC14D35540D0C1A4B5BE25DAFF4F582506FB82ABC6E2E301039D1AC1A83780DF45D1F3780587B3EE326FD7486BCFFBF161457D080516FD9AE639C672F9CC' + ';'
    _csrf = '_csrf=' + cookies['_csrf'] + ';'
    _pv0 = '_pv0=' + cookies['_pv0'] + ';'
    _pf0 = '_pf0=' + cookies['_pf0'] + ';'
    _pc0 = '_pc0=' + cookies['_pc0'] + ';'
    iPlanetDirectoryPro = 'iPlanetDirectoryPro=' + cookies[
        'iPlanetDirectoryPro'] + ';'
    sso_tyb_token = 'sso_tyb_token=' + cookies['sso_tyb_token']
    cookie = ' '.join([
        JSESSIONID, _ga, wsess, sudy_ck, _csrf, _pv0, _pf0, _pc0,
        iPlanetDirectoryPro, sso_tyb_token
    ])

    headers = {
        "Accept":
        "application/json, text/plain, */*",
        "Accept-Encoding":
        "gzip, deflate",
        "Accept-Language":
        "zh-CN,zh;q=0.9",
        "app-key":
        app_key,
        "Connection":
        "keep-alive",
        "Content-Type":
        "application/x-www-form-urlencoded",
        "Cookie":
        cookie,
        "Host":
        "www.tyys.zju.edu.cn",
        "Referer":
        "http://www.tyys.zju.edu.cn/venue/reservation",
        "sso-token":
        cookies['sso_tyb_token'],
        "User-Agent":
        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.135 Safari/537.36",
    }

    # login
    url = 'http://www.tyys.zju.edu.cn/venue-server/api/login'
    timestamp = datetime.timestamp(datetime.now())
    timestamp = str(int(timestamp)) + '000'
    headers['timestamp'] = timestamp
    headers['sign'] = get_login_sign(timestamp)
    data = parse.urlencode({})
    res = sess.post(url, data=data, headers=headers)
    content = json.loads(res.content.decode())
    cgAuthorization = content['data']['token']['access_token']
    headers['cgAuthorization'] = cgAuthorization

    # role login
    url = 'http://www.tyys.zju.edu.cn/venue-server/roleLogin'
    timestamp = datetime.timestamp(datetime.now())
    timestamp = str(int(timestamp)) + '000'
    headers['timestamp'] = timestamp
    headers['sign'] = get_rolelogin_sign(timestamp)
    data = parse.urlencode({'roleid': 3})
    res = sess.post(url, data=data, headers=headers)
    content = json.loads(res.content.decode())
    cgAuthorization = content['data']['token']['access_token']
    headers['cgAuthorization'] = cgAuthorization

    # test if login successfully
    # timestamp = datetime.timestamp(datetime.now())
    # timestamp = str(int(timestamp)) + '000'
    # headers['timestamp'] = timestamp
    # headers['sign'] = get_reservation_sign(timestamp)
    # url = 'http://www.tyys.zju.edu.cn/venue-server/api/protocols/code/RESERVATION_PROTOCOL?nocache=' + timestamp
    # res = sess.get(url, headers=headers)
    # content = res.content.decode()

    day = datetime.now() + timedelta(days=2)
    day = str(day).split(' ')[0]

    timestamp = datetime.timestamp(datetime.now())
    timestamp = str(int(timestamp)) + '000'

    url = 'http://www.tyys.zju.edu.cn/venue-server/api/reservation/day/info?venueSiteId=23&searchDate={}&nocache={}'.format(
        day, timestamp)
    headers['timestamp'] = timestamp
    headers['sign'] = get_timeid_sign(timestamp, day)
    res = sess.get(url, headers=headers)
    content = json.loads(res.content.decode())

    # select timeids
    time_infos = content['data']['spaceTimeInfo']
    timeids = []
    for time_info in time_infos:
        hour = int(time_info['beginTime'].split(':')[0])
        if hour >= 16:
            timeids.append(str(time_info['id']))

    spaces = content['data']['reservationDateSpaceInfo'][day]
    spaceids = [str(space['id']) for space in spaces]
    spaceids = spaceids[1::2][:4]
    reservations = []
    for spaceid in spaceids:
        for timeid in timeids:
            spaceId = '"spaceId": "' + str(spaceid) + '"'
            timeId = '"timeId": "' + str(timeid) + '"'
            json_str = '{' + ','.join(
                [spaceId, timeId, '"venueSpaceGroupId":null']) + '}'
            json_str = '[' + json_str + ']'
            reservations.append(json_str)
        timeids = timeids[::-1]

    # select space
    for reservation in reservations:
        try:
            url = 'http://www.tyys.zju.edu.cn/venue-server/api/reservation/order/info'
            data = {
                "venueSiteId": "23",
                "reservationDate": day,
                "weekStartDate": day,
                "reservationOrderJson": reservation,
                "isOfflineTicket": "0",
            }
            timestamp = datetime.timestamp(datetime.now())
            timestamp = str(int(timestamp)) + '000'
            headers['timestamp'] = timestamp
            headers['sign'] = get_order_sign(timestamp, data)
            data = parse.urlencode(data)
            res = sess.post(url, data=data, headers=headers)
            content = res.content.decode()
            print(content)

            # submit order
            url = 'http://www.tyys.zju.edu.cn/venue-server/api/reservation/order/submit'
            content = json.loads(content)
            venueInfoBean = content['data']['venueInfoBean']
            orders = content['data']['orderDetailList']
            order = orders[0]
            spaceId = '"spaceId": "' + str(order['venueSpaceId']) + '"'
            timeId = '"timeId": "' + str(order['timeId']) + '"'
            json_str = '{' + ','.join(
                [spaceId, timeId, '"venueSpaceGroupId":null']) + '}'
            json_str = '[' + json_str + ']'

            data = {
                "venueSiteId": str(venueInfoBean['venueSiteId']),
                "reservationDate": order['startDate'].split(' ')[0],
                "reservationOrderJson": json_str,
                "phone": str(content['data']['phone']),
                "buddyIds": str(content['data']['buddyList'][0]['id']),
                "weekStartDate": order['startDate'].split(' ')[0],
                "isOfflineTicket": "1",
            }

            timestamp = datetime.timestamp(datetime.now())
            timestamp = str(int(timestamp)) + '000'
            headers['timestamp'] = timestamp
            headers['sign'] = get_submit_sign(timestamp, data)
            data = parse.urlencode(data)
            res = sess.post(url, data=data, headers=headers)
            content = res.content.decode()
            print(content)

            tradeNo = json.loads(content)['data']['orderInfo']['tradeNo']

            # pay
            url = 'http://www.tyys.zju.edu.cn/venue-server/api/venue/finances/order/pay'
            data = {
                "venueTradeNo": tradeNo,
            }
            headers['timestamp'] = timestamp
            headers['sign'] = get_pay_sign(timestamp, tradeNo)

            data = parse.urlencode(data)
            res = sess.post(url, data=data, headers=headers)
            print(res.content.decode())
        except:
            print(reservation)


def main():
    username = ''
    password = ''
    order(username, password)


main()

# Schedule task
scheduler = BlockingScheduler()
hour = 8
minute = 0
scheduler.add_job(main, 'cron', args=[], hour=hour, minute=minute, second=3)
scheduler.start()
