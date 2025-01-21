yum -y install leveldb-devel.x86_64

for PYBIN in /opt/python/*/bin; do
    echo "Building for ${PYBIN} "
    ${PYBIN}/pip install cython
    ${PYBIN}/pip install setuptools
    ${PYBIN}/python setup.py bdist_wheel
done

for whl in dist/*-linux*.whl; do
    auditwheel repair "$whl" -w  dist/.
done
