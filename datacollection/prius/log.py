# Copyright (C) 2017 Swift Navigation Inc.
# Contact: Swift Navigation <dev@swiftnav.com>
#
# This source is subject to the license found in the file 'LICENSE' which must
# be be distributed together with this source. All other rights reserved.
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
# EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
"""
the :mod:`sbp.client.examples.simple` module contains a basic example of
reading SBP messages from a serial port, decoding BASELINE_NED messages and
printing them out.
"""

import argparse
from sbp.client.drivers.network_drivers import TCPDriver
from sbp.client import Handler, Framer
from sbp.navigation import SBP_MSG_BASELINE_NED, SBP_MSG_POS_LLH


def main():
    parser = argparse.ArgumentParser(
        description="Swift Navigation SBP Example.")
    parser.add_argument(
        "-a",
        "--host",
        default='localhost',
        help="specify the host address.")
    parser.add_argument(
        "-p",
        "--port",
        default=55555,
        help="specify the port to use.")
    args = parser.parse_args()

    # Open a connection to Piksi using TCP
    with TCPDriver(args.host, args.port) as driver:
        with Handler(Framer(driver.read, None, verbose=True)) as source:
            try:
                for msg, metadata in source.filter(SBP_MSG_POS_LLH):
                    # Print out the N, E, D coordinates of the baseline
                    print("%d,%.16f,%.16f,%.16f,%d,%d,%d,%d" % (msg.tow, msg.lat, msg.lon,
                                              msg.height, msg.h_accuracy, msg.v_accuracy, msg.n_sats, msg.flags))
            except KeyboardInterrupt:
                pass


if __name__ == "__main__":
    main()
