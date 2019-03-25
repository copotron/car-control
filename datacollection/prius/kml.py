import argparse
from sbp.client.drivers.network_drivers import TCPDriver
from sbp.client import Handler, Framer
from sbp.navigation import SBP_MSG_BASELINE_NED, SBP_MSG_POS_LLH
from geopy.distance import vincenty


def main():
    parser = argparse.ArgumentParser(
        description="Export position suitable for KML file.")
    parser.add_argument(
        "-a",
        "--host",
        default='192.168.5.51',
        help="specify the host address.")
    parser.add_argument(
        "-p",
        "--port",
        default=55555,
        help="specify the port to use.")
    args = parser.parse_args()
    prev = None;
    # Open a connection to Piksi using TCP
    with TCPDriver(args.host, args.port) as driver:
        with Handler(Framer(driver.read, None, verbose=True)) as source:
            try:
                for msg, metadata in source.filter(SBP_MSG_POS_LLH):
                    cur = (msg.lat, msg.lon)
                    if prev:
                        dist = vincenty(prev, cur).meters
                        #print(dist)
                        if dist > 0.1:    
                            print("%.16f,%.16f,%.16f" % (msg.lon, msg.lat, msg.height))
                            prev = cur
                    else:
                        prev = cur
            except KeyboardInterrupt:
                pass


if __name__ == "__main__":
    main()
