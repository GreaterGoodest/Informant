#!/usr/bin/env python3
import sys
import mmap
from typing import ByteString


def load_payload(payload_path: str) -> ByteString:
    """ loads payload data for processing 

        Args:
            payload_path: file system path to compiled payload 

        Returns:
            payload binary data

    """
    return ""


def pad_payload(payload_data: ByteString) -> ByteString:
    """ padds payload to 512 bytes 
    
        Args:
            payload_data: loaded binary payload data

        Returns:
            padded binary payload data

    """
    return ""


def stamp_data(informant_path: str, padded_payload: ByteString) -> None:
    """ Use mmap to avoid loading entire informant binary into memory.
        Locat stampable data portion of informant binary, then
        stamp with padded payload.

        Args:
            informant_path: path to informant binary
            padded_paylaod: padded binary payload to inject into target binary

    """

    ''' Example mmap usage '''
    #with open("hugefile", "rw+b") as f:
    #    mm = mmap.mmap(f.fileno(), 0)
    #    print(mm.find('\x00\x09\x03\x03'))


def stamp_payload(payload_path: str, informant_path: str):
    """ Main function for stamping informant with payload to eventually place in target binary """
    payload_data = load_payload(payload_path)
    padded_payload = pad_payload(payload_data)

    informant_path = ""
    stamp_data(informant_path, padded_payload)


def print_help() -> None:
    print("Usage: ./stamper.py [payload path] [informant path]")


if __name__ == "__main__":
    if len(sys.argv[1]) < 3:
        print_help()
        exit(1)
    payload_path = sys.argv[1]
    informant_path = sys.argv[2]
    stamp_payload(payload_path, informant_path)