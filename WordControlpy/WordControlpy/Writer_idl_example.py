#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file Writer_idl_examplefile.py
 @brief Python example implementations generated from Writer.idl
 @date $Date$


 LGPL

"""

import omniORB
from omniORB import CORBA, PortableServer
import Writer, Writer__POA


class mWriter_i (Writer__POA.mWriter):
    """
    @class mWriter_i
    Example class implementing IDL interface Writer.mWriter
    """

    def __init__(self):
        """
        @brief standard constructor
        Initialise member variables here
        """
        pass

    # float oCurrentCursorPositionX()
    def oCurrentCursorPositionX(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # float oCurrentCursorPositionY()
    def oCurrentCursorPositionY(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # void gotoStart(in boolean sel)
    def gotoStart(self, sel):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: None

    # void gotoEnd(in boolean sel)
    def gotoEnd(self, sel):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: None

    # void gotoStartOfLine(in boolean sel)
    def gotoStartOfLine(self, sel):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: None

    # void gotoEndOfLine(in boolean sel)
    def gotoEndOfLine(self, sel):
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
    servant = mWriter_i()

    # Activate it in the Root POA
    poa.activate_object(servant)

    # Get the object reference to the object
    objref = servant._this()
    
    # Print a stringified IOR for it
    print orb.object_to_string(objref)

    # Activate the Root POA's manager
    poa._get_the_POAManager().activate()

    # Run the ORB, blocking this thread
    orb.run()

