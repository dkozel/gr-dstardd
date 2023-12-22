#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: D-Star DD Transceiver
# Author: Hansi Reiser dl9rdz
# GNU Radio version: 3.10.8.0

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio import analog
from gnuradio import blocks
from gnuradio import digital
from gnuradio import dstardd
from gnuradio import filter
from gnuradio.filter import firdes
from gnuradio import gr
from gnuradio.fft import window
import sys
import signal
from PyQt5 import Qt
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio import network
from gnuradio import uhd
import time
from gnuradio.qtgui import Range, RangeWidget
from PyQt5 import QtCore



class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "D-Star DD Transceiver", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("D-Star DD Transceiver")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except BaseException as exc:
            print(f"Qt GUI: Could not set Icon: {str(exc)}", file=sys.stderr)
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "top_block")

        try:
            geometry = self.settings.value("geometry")
            if geometry:
                self.restoreGeometry(geometry)
        except BaseException as exc:
            print(f"Qt GUI: Could not restore geometry: {str(exc)}", file=sys.stderr)

        ##################################################
        # Variables
        ##################################################
        self.verbosex = verbosex = True
        self.variable_qtgui_check_box_0 = variable_qtgui_check_box_0 = True
        self.tx_power = tx_power = 70
        self.squelch = squelch = -70
        self.samp_rate = samp_rate = 1024000
        self.freq = freq = int(1242.45e6)

        ##################################################
        # Blocks
        ##################################################

        self._tx_power_range = Range(0, 80, 1, 70, 200)
        self._tx_power_win = RangeWidget(self._tx_power_range, self.set_tx_power, "TX Power", "counter_slider", int, QtCore.Qt.Horizontal)
        self.top_layout.addWidget(self._tx_power_win)
        _variable_qtgui_check_box_0_check_box = Qt.QCheckBox("'variable_qtgui_check_box_0'")
        self._variable_qtgui_check_box_0_choices = {True: True, False: False}
        self._variable_qtgui_check_box_0_choices_inv = dict((v,k) for k,v in self._variable_qtgui_check_box_0_choices.items())
        self._variable_qtgui_check_box_0_callback = lambda i: Qt.QMetaObject.invokeMethod(_variable_qtgui_check_box_0_check_box, "setChecked", Qt.Q_ARG("bool", self._variable_qtgui_check_box_0_choices_inv[i]))
        self._variable_qtgui_check_box_0_callback(self.variable_qtgui_check_box_0)
        _variable_qtgui_check_box_0_check_box.stateChanged.connect(lambda i: self.set_variable_qtgui_check_box_0(self._variable_qtgui_check_box_0_choices[bool(i)]))
        self.top_layout.addWidget(_variable_qtgui_check_box_0_check_box)
        self.uhd_usrp_source_0 = uhd.usrp_source(
            ",".join(('type=b200', "")),
            uhd.stream_args(
                cpu_format="fc32",
                otw_format="sc16",
                args='',
                channels=list(range(0,1)),
            ),
        )
        self.uhd_usrp_source_0.set_subdev_spec('A:A', 0)
        self.uhd_usrp_source_0.set_samp_rate(samp_rate)
        self.uhd_usrp_source_0.set_time_unknown_pps(uhd.time_spec(0))

        self.uhd_usrp_source_0.set_center_freq(freq, 0)
        self.uhd_usrp_source_0.set_antenna('TX/RX', 0)
        self.uhd_usrp_source_0.set_gain(40, 0)
        self.uhd_usrp_sink_0 = uhd.usrp_sink(
            ",".join(('type=b200', "")),
            uhd.stream_args(
                cpu_format="fc32",
                otw_format="sc16",
                args='',
                channels=list(range(0,1)),
            ),
            '',
        )
        self.uhd_usrp_sink_0.set_subdev_spec('A:A', 0)
        self.uhd_usrp_sink_0.set_samp_rate(samp_rate)
        self.uhd_usrp_sink_0.set_time_unknown_pps(uhd.time_spec(0))

        self.uhd_usrp_sink_0.set_center_freq(freq, 0)
        self.uhd_usrp_sink_0.set_antenna('TX/RX', 0)
        self.uhd_usrp_sink_0.set_bandwidth(samp_rate, 0)
        self.uhd_usrp_sink_0.set_gain(tx_power, 0)
        self.network_tuntap_pdu_0 = network.tuntap_pdu('dstar0', 10000, False)
        self.low_pass_filter_0 = filter.fir_filter_ccf(
            2,
            firdes.low_pass(
                1,
                samp_rate,
                200e3,
                60e3,
                window.WIN_HAMMING,
                6.76))
        self.dstardd_dstardd_encoder_0 = dstardd.dstardd_encoder('DG1NGN', 'DG8NGN', 'CQCQCQ', 'CQCQCQ', True)
        self.dstardd_dstardd_decoder_0 = dstardd.dstardd_decoder(verbosex)
        self.digital_gmsk_mod_0 = digital.gmsk_mod(
            samples_per_symbol=8,
            bt=0.5,
            verbose=False,
            log=False,
            do_unpack=True)
        self.digital_gmsk_demod_0 = digital.gmsk_demod(
            samples_per_symbol=4,
            gain_mu=(0.175+0.3),
            mu=0.5,
            omega_relative_limit=(0.050/5),
            freq_error=(0.0102*0),
            verbose=False,log=False)
        self.blocks_multiply_const_vxx_1 = blocks.multiply_const_cc(0.5)


        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.dstardd_dstardd_decoder_0, 'pdu'), (self.network_tuntap_pdu_0, 'pdus'))
        self.msg_connect((self.network_tuntap_pdu_0, 'pdus'), (self.dstardd_dstardd_encoder_0, 'pdu'))
        self.connect((self.blocks_multiply_const_vxx_1, 0), (self.uhd_usrp_sink_0, 0))
        self.connect((self.digital_gmsk_demod_0, 0), (self.dstardd_dstardd_decoder_0, 0))
        self.connect((self.digital_gmsk_mod_0, 0), (self.blocks_multiply_const_vxx_1, 0))
        self.connect((self.dstardd_dstardd_encoder_0, 0), (self.digital_gmsk_mod_0, 0))
        self.connect((self.low_pass_filter_0, 0), (self.digital_gmsk_demod_0, 0))
        self.connect((self.uhd_usrp_source_0, 0), (self.low_pass_filter_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_verbosex(self):
        return self.verbosex

    def set_verbosex(self, verbosex):
        self.verbosex = verbosex

    def get_variable_qtgui_check_box_0(self):
        return self.variable_qtgui_check_box_0

    def set_variable_qtgui_check_box_0(self, variable_qtgui_check_box_0):
        self.variable_qtgui_check_box_0 = variable_qtgui_check_box_0
        self._variable_qtgui_check_box_0_callback(self.variable_qtgui_check_box_0)

    def get_tx_power(self):
        return self.tx_power

    def set_tx_power(self, tx_power):
        self.tx_power = tx_power
        self.uhd_usrp_sink_0.set_gain(self.tx_power, 0)

    def get_squelch(self):
        return self.squelch

    def set_squelch(self, squelch):
        self.squelch = squelch
        self.analog_pwr_squelch_xx_0.set_threshold(self.squelch)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, 200e3, 60e3, window.WIN_HAMMING, 6.76))
        self.uhd_usrp_sink_0.set_samp_rate(self.samp_rate)
        self.uhd_usrp_sink_0.set_bandwidth(self.samp_rate, 0)
        self.uhd_usrp_source_0.set_samp_rate(self.samp_rate)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self.uhd_usrp_sink_0.set_center_freq(self.freq, 0)
        self.uhd_usrp_source_0.set_center_freq(self.freq, 0)




def main(top_block_cls=top_block, options=None):

    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    qapp.exec_()

if __name__ == '__main__':
    main()
