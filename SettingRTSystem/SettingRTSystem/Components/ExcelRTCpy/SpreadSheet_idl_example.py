#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file SpreadSheet_idl_examplefile.py
 @brief Python example implementations generated from SpreadSheet.idl
 @date $Date$


 LGPL

"""

import omniORB
from omniORB import CORBA, PortableServer
import SpreadSheet, SpreadSheet__POA


class mSpreadSheet_i (SpreadSheet__POA.mSpreadSheet):
    """
    @class mSpreadSheet_i
    Example class implementing IDL interface SpreadSheet.mSpreadSheet
    """

    def __init__(self):
        """
        @brief standard constructor
        Initialise member variables here
        """
        pass

    # string get_string(in string l, in string c, in string sn)
    def get_string(self, l, c, sn):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # void set_value(in string l, in string c, in string sn, in float v)
    def set_value(self, l, c, sn, v):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: None

    # StringList get_string_range(in string l1, in string c1, in string l2, in string c2, in string sn)
    def get_string_range(self, l1, c1, l2, c2, sn):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # void set_value_range(in string l, in string c, in string sn, in FloatList v)
    def set_value_range(self, l, c, sn, v):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: None

    # void set_string(in string l, in string c, in string sn, in string v)
    def set_string(self, l, c, sn, v):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: None

    # void set_string_range(in string l, in string c, in string sn, in StringList v)
    def set_string_range(self, l, c, sn, v):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: None


if __name__ == "__main__":
    import sys
    
    # Initialise the ORB
    orb = CORBA.ORB_init(sys.argv)
    
    # As an example, we activate an object in the Root POA
    poa = orb.resolve_initial_references("RootPOA")

    # Create an instance of a servant class
    servant = mSpreadSheet_i()

    # Activate it in the Root POA
    poa.activate_object(servant)

    # Get the object reference to the object
    objref = servant._this()
    
    # Print a stringified IOR for it
    print(orb.object_to_string(objref))

    # Activate the Root POA's manager
    poa._get_the_POAManager().activate()

    # Run the ORB, blocking this thread
    orb.run()

