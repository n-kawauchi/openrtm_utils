#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
from PyQt4 import QtGui,QtWebKit,QtCore


def format(color, style=''):

    _color = QtGui.QColor()
    _color.setNamedColor(color)

    _format = QtGui.QTextCharFormat()
    _format.setForeground(_color)
    if 'bold' in style:
        _format.setFontWeight(QtGui.QFont.Bold)
    if 'italic' in style:
        _format.setFontItalic(True)

    return _format


STYLES = {
    'keyword': format('blue'),
    'operator': format('red'),
    'brace': format('darkGray'),
    'defclass': format('black', 'bold'),
    'string': format('magenta'),
    'string2': format('darkMagenta'),
    'comment': format('darkGreen', 'italic'),
    'self': format('black', 'bold'),
    'numbers': format('brown'),
}


class Highlighter (QtGui.QSyntaxHighlighter):
    keywords = [
        'and', 'assert', 'break', 'class', 'continue', 'def',
        'del', 'elif', 'else', 'except', 'exec', 'finally',
        'for', 'from', 'global', 'if', 'import', 'in',
        'is', 'lambda', 'not', 'or', 'pass', 'print',
        'raise', 'return', 'try', 'while', 'yield',
        'None', 'True', 'False',
    ]
    operators = [
        '=',

        '==', '!=', '<', '<=', '>', '>=',

        '\+', '-', '\*', '/', '//', '\%', '\*\*',

        '\+=', '-=', '\*=', '/=', '\%=',

        '\^', '\|', '\&', '\~', '>>', '<<',
    ]
    braces = [
        '\{', '\}', '\(', '\)', '\[', '\]',
    ]
    def __init__(self, document):
        QtGui.QSyntaxHighlighter.__init__(self, document)
        rules = []
        self.tri_single = (QtCore.QRegExp("'''"), 1, STYLES['string2'])
        self.tri_double = (QtCore.QRegExp('"""'), 2, STYLES['string2'])

        rules = []


        rules += [(r'\b%s\b' % w, 0, STYLES['keyword']) for w in Highlighter.keywords]
        rules += [(r'%s' % o, 0, STYLES['operator']) for o in Highlighter.operators]
        rules += [(r'%s' % b, 0, STYLES['brace']) for b in Highlighter.braces]


        rules += [

            (r'\bself\b', 0, STYLES['self']),


            (r'"[^"\\]*(\\.[^"\\]*)*"', 0, STYLES['string']),

            (r"'[^'\\]*(\\.[^'\\]*)*'", 0, STYLES['string']),


            (r'\bdef\b\s*(\w+)', 1, STYLES['defclass']),

            (r'\bclass\b\s*(\w+)', 1, STYLES['defclass']),


            (r'#[^\n]*', 0, STYLES['comment']),


            (r'\b[+-]?[0-9]+[lL]?\b', 0, STYLES['numbers']),
            (r'\b[+-]?0[xX][0-9A-Fa-f]+[lL]?\b', 0, STYLES['numbers']),
            (r'\b[+-]?[0-9]+(?:\.[0-9]+)?(?:[eE][+-]?[0-9]+)?\b', 0, STYLES['numbers']),
        ]
        self.rules = [(QtCore.QRegExp(pat), index, fmt) for (pat, index, fmt) in rules]

    def highlightBlock(self, text):

        for expression, nth, format in self.rules:
            index = expression.indexIn(text, 0)

            while index >= 0:

                index = expression.pos(nth)
                length = expression.cap(nth).length()
                self.setFormat(index, length, format)
                index = expression.indexIn(text, index + length)

        self.setCurrentBlockState(0)


        in_multiline = self.match_multiline(text, *self.tri_single)
        if not in_multiline:
            in_multiline = self.match_multiline(text, *self.tri_double)


    def match_multiline(self, text, delimiter, in_state, style):

        if self.previousBlockState() == in_state:
            start = 0
            add = 0

        else:
            start = delimiter.indexIn(text)

            add = delimiter.matchedLength()

        while start >= 0:

            end = delimiter.indexIn(text, start + add)

            if end >= add:
                length = end - start + add + delimiter.matchedLength()
                self.setCurrentBlockState(0)

            else:
                self.setCurrentBlockState(in_state)
                length = text.length() - start + add

            self.setFormat(start, length, style)

            start = delimiter.indexIn(text, start + length)


        if self.currentBlockState() == in_state:
            return True
        else:
            return False
