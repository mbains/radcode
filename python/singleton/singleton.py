class Klass(object):

    class __impl:
        def spam(self):
            return id(self)

    __instance = None

    def __init__(self):

        if Klass.__instance is None:
            Klass.__instance = Klass.__impl()

        self.__dict__['_Klass__instance'] = Klass.__instance

    def __getattr__(self, attr):
        """ Delegate access to implementation """
        return getattr(self.__instance, attr)

    def __setattr__(self, attr, value):
        """ Delegate access to implementation """
        return setattr(self.__instance, attr, value)

    def init(self):
        '''This class is a singleton, needs explicit init'''
        pass

