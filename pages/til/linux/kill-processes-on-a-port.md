# Kill processes on a port

It's advised to first check the running processing on a port, i.e. for TCP on port 4000: `sudo lsof -i TCP:4000`.

## How To

To kill all processes on a port while using Linux, i.e. TCP on port 4000: `fuser -k 4000/tcp`.

## References

- [How to kill process based on the port number in Linux](https://linuxconfig.org/how-to-kill-process-based-on-the-port-number-in-linux)