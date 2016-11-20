How to run these benchmarks
===========================

These bencharks were run on linux (in my case I used a Vagrant VM - box 'ubuntu/trusty64'.

You'll need to install the packages you want to test, and to update the Makefile 
so that the headers are found.

Original benchmark with higher key count and restricted to just random integer inserts:

    $ cd hash-table-shootout
    $ mkdir build
    $ make
    $ python bench.py
    $ python make_chart_data.py < output | python make_html.py

Your charts are now in charts.html.

You can tweak some of the values in bench.py to make it run faster at the
expense of less granular data, and you might need to tweak some of the `tickSize`
settings in `charts-template.html`.

To run the benchmark at the highest priority possible, do this:

    $ sudo nice -n-20 ionice -c1 -n0 sudo -u $USER python bench.py

Copyright Information
=====================

Modified by Gregory Popovitch in 2016

Modified by Timon Karnezos in 2011.

Originally written by Nick Welch in 2010.

No copyright.  This work is dedicated to the public domain.

For full details, see http://creativecommons.org/publicdomain/zero/1.0/


From https://github.com/aggregateknowledge
==========================================

I ran this on an Amazon EC2 `m2.4xlarge` instance with the Red Hat 6.1 x86\_64 AMI (`ami-31d41658`).

Setup:
------

    $ yum install make-3.81-19.el6.x86_64            \
                gcc-4.4.5-6.el6.x86_64               \
                gcc-c++-4.4.5-6.el6.x86_64           \
                python-devel-2.6.6-20.el6.x86_64     \
                glib2-devel-2.22.5-6.el6.x86_64      \
                boost-devel-1.41.0-11.el6_1.2.x86_64 \
                qt-devel-4.6.2-17.el6_1.1.x86_64     \
                git

    $ wget http://google-sparsehash.googlecode.com/files/sparsehash-1.11-1.noarch.rpm
    $ rpm -i sparsehash-1.11-1.noarch.rpm
    $ git clone git://github.com/timonk/hash-table-shootout.git

