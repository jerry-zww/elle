# -*- encoding: utf-8 -*-

import socket
import json

import meta.page
import database

from twisted.python import log

FILE_TRANSFER = 7
FILE_TRANSFER_STATUS = 11
USER_STATUS = 8
MESSAGE = 217
LOGGED_IN = 666

class Notifier(object):

        def open(self):
                raise Exception('Not implemented')
	def notify_one(self, notif_id, to, message):
                raise Exception('Not implemented')
	def notify_some(self, notif_id, to, message):
                raise Exception('Not implemented')
        def send_notification(self, message):
                raise Exception('Not implemented')
	def close(self):
                raise Exception('Not implemented')

class TrophoniusNotify(Notifier):
	def __init__(self):
		self.conn = socket.socket()

	def open(self):
		self.conn.connect(("localhost", 23457))

        def send_notification(self, message):
                if isinstance(message, dict):
			msg = json.dumps(message, default = str)
		# elif isinstance(message, str):
		# 	msg = message + json.dumps(_dict, default = str)
                else:
                        log.err('Notification was bad formed.')

                print(" ".format(msg))
		self.conn.send("{}\n".format(msg))

        def _add_notif_to_db(self, recipient_id, notif):
                user_ = database.users().find_one(
                            database.ObjectId(recipient_id));

                if not user_:
                        return None

                user_['notifications'].append(notif)
                database.users().save(user_)

                return user_

	def notify_one(self, notification_id, recipient_id, message):

                message['notification_id'] = notification_id;

                user_ = self._add_notif_to_db(recipient_id, message)

                if not user_:
                        log.err("Unknown user.")
                        return

                if user_['connected']:
                        dict_ = {'recipient_id': str(recipient_id)}
                        dict_.update(message)
                        self.send_notification(dict_)

        def notify_some(self, notification_id, recipients_id, message):
                print("Original message {}\n".format(message));
                if not isinstance(recipients_id, list):
                        return self.notify_one(notification_id, recipients_id, message)

                for _id in recipients_id:
                        self._add_notif_to_db(_id, message)

                dict_ = {'recipient_id': recipients_id, 'notification_id' : notification_id}
                dict_.update(message)
                self.send_notification(dict_)
