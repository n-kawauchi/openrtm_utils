#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

class ActivityCode:
    onInitialize = 0
    onFinalize = 1
    onStartup = 2
    onShutdown = 3
    onActivated = 4
    onDeactivated = 5
    onExecute = 6
    onAborting = 7
    onError = 8
    onReset = 9
    onStateUpdate = 10
    onRateChanged = 11
    num = 12

    def __init__(self):
        pass
    @staticmethod
    def toString(id):
        if id == ActivityCode.onInitialize:
            return "onInitialize"
        elif id == ActivityCode.onFinalize:
            return "onFinalize"
        elif id == ActivityCode.onStartup:
            return "onStartup"
        elif id == ActivityCode.onShutdown:
            return "onShutdown"
        elif id == ActivityCode.onActivated:
            return "onActivated"
        elif id == ActivityCode.onDeactivated:
            return "onDeactivated"
        elif id == ActivityCode.onExecute:
            return "onExecute"
        elif id == ActivityCode.onAborting:
            return "onAborting"
        elif id == ActivityCode.onError:
            return "onError"
        elif id == ActivityCode.onReset:
            return "onReset"
        elif id == ActivityCode.onStateUpdate:
            return "onStateUpdate"
        elif id == ActivityCode.onRateChanged:
            return "onRateChanged"
        else:
            return ""
        
        

		