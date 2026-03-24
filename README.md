# py-msilib

Read and write Microsoft Installer files.

This library is legacy code borrowed from Python 3.12, intended to allow
cx_Freeze's `bdist_msi` command to continue working in Python 3.13+.

[![PyPI version](https://img.shields.io/pypi/v/py-msilib)](https://pypi.org/project/py-msilib/)
[![PyPi Downloads](https://img.shields.io/pypi/dm/py-msilib)](https://pypistats.org/packages/py-msilib)
[![Conda Version](https://img.shields.io/conda/vn/conda-forge/py-msilib.svg)](https://anaconda.org/conda-forge/py-msilib)
[![Conda Downloads](https://anaconda.org/conda-forge/py-msilib/badges/downloads.svg)](https://anaconda.org/conda-forge/py-msilib)
[![Python](https://img.shields.io/pypi/pyversions/py-msilib)](https://www.python.org/)
[![Coverage](https://raw.githubusercontent.com/aneiosi/py-msilib/python-coverage-comment-action-data/badge.svg)](https://htmlpreview.github.io/?https://github.com/aneiosi/py-msilib/blob/python-coverage-comment-action-data/htmlcov/index.html)
[![Ruff](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/astral-sh/ruff/main/assets/badge/v2.json)](https://github.com/astral-sh/ruff)
[![prek](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/j178/prek/master/docs/assets/badge-v0.json)](https://github.com/j178/prek)

## Installation

Choose the Python package manager according to your system. See how the
installation works with the most common ones, which are pip and conda.

To install the latest version of `py-msilib` into a virtual environment:

```sh
uv pip install --upgrade py-msilib
```

If using pip:

```sh
pip install --upgrade py-msilib
```

From the conda-forge channel:

```sh
conda install conda-forge::py-msilib
```

To install the latest development build:

```sh
uv pip uninstall py-msilib
uv pip install --extra-index-url https://test.pypi.org/simple/ py-msilib --prerelease=allow --index-strategy=unsafe-best-match
```

If using pip:

```sh
pip uninstall py-msilib
pip install --extra-index-url https://test.pypi.org/simple/ py-msilib --pre --no-cache
```

## Documentation

Please read the documentation at Python
[docs](https://docs.python.org/3.12/library/msilib.html).
