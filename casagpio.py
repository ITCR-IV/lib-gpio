import ctypes
import pathlib
import errno

# Load the shared library into ctypes
c_lib = ctypes.CDLL("libcasagpio.so")

def init_gpio():
    ret = c_lib.init_gpio()
    if(ret):
        print("ERROR: couldn't get hold of GPIO chip 0")
        raise OSError(errno.EACCES, "Couldn't access GPIO chip 0");

def close_gpio():
    ret = c_lib.close_gpio()

def write_pin(pin_number, value):
    ret = c_lib.write_pin(ctypes.c_size_t(pin_number), ctypes.c_int(value))

    if(ret == -1):
        print("ERROR: called write_pin without calling init_gpio")
        raise RuntimeError("Attempted write to a pin without initializing gpio");
    elif(ret == 1):
        print("ERROR: couldn't get hold of GPIO line", pin_number)
        raise OSError(errno.EACCES, f"Couldn't access GPIO line {pin_number}");
    elif(ret == 2):
        print(f"ERROR: couldn't request GPIO line {pin_number} as output")
        raise OSError(errno.EACCES, f"Couldn't request GPIO line {pin_number} as output");
    elif(ret == 3):
        print(f"ERROR: couldn't write {value} to GPIO line {pin_number}")
        raise OSError(errno.EACCES, f"Couldn't write {value} to GPIO line {pin_number}");

def read_pin(pin_number):
    value = ctypes.c_int();

    ret = c_lib.read_pin(ctypes.c_size_t(pin_number), ctypes.byref(value))

    if(ret == -1):
        print("ERROR: called read_pin without calling init_gpio")
        raise RuntimeError("Attempted reading a pin without initializing gpio");
    if(ret == 1):
        print("ERROR: couldn't get hold of GPIO line", pin_number)
        raise OSError(errno.EACCES, f"Couldn't access GPIO line {pin_number}");
    elif(ret == 2):
        print(f"ERROR: couldn't request GPIO line {pin_number} as input")
        raise OSError(errno.EACCES, f"Couldn't request GPIO line {pin_number} as output");
    elif(ret == 3):
        print(f"ERROR: couldn't read GPIO line {pin_number}")
        raise OSError(errno.EACCES, f"Couldn't read GPIO line {pin_number}");

    return value.value
