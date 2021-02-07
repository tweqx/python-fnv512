# fnv512

fnv512 is a Python implementation for the FNV-0/FNV-1/FNV-1A 512 bits hashing algorithms

## Installation

To install, clone the repository and run :
```bash
python3 setup.py install
```

You might need to use `sudo`.

## Usage

```python
import fnv512

fnv512.fnv0(b'chongo <Landon Curt Noll> /\\../\\')
# 'b86db0b1171f4416dca1e50f309990acac87d059c90000000000000000000d21e948f68a34c192f62ea79bc942dbe7ce182036415f56e34bac982aac4afe9fd9'
fnv512.fnv1('foobar')
# 'b0ec738d9c6fd969d05f0b35f6c0effd20209465290000004bf99f58ee4196afb9700e20110830fea5396b76280e47fd022b6e81331ca1a9cf6faf7123c3fc56'
fnv512.fnv1a('foobar')
# 'b0ec738d9c6fd969d05f0b35f6c0ed53adcacccd8e0000004bf99f58ee4196afb9700e20110830fea5396b76280e47fd022b6e81331ca1a9ced729c364be7788'
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)
