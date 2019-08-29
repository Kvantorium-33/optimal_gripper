#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String
from pocketsphinx import LiveSpeech, get_model_path
import os


model = get_model_path()

speech = LiveSpeech(
    verbose = False,
    sampling_rate = 16000,
    buffer_size = 2048,
    no_search = False,
    full_utt = False,
    hmm = os.path.join(model, 'ru-ru'),
    lm = os.path.join(model, 'ru.lm.bin'),
    dic = os.path.join(model, 'ruDict.dict')
)

def pub(command):
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    str = command
    rospy.loginfo(str)
    pub.publish(str)
print("ready")
if __name__ == '__main__':
    try:
        for text in speech:
            if rospy.is_shutdown():
                break
            pub(text)
    except rospy.ROSInterruptException:
        pass
