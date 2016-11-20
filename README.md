How to run these benchmarks
===========================

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

To run:
-------

Nick's original benchmark with higher key count and restricted to just random integer inserts:

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

since I'm running this as `root` on EC2, it's simply:

    $ nice -n-20 ionice -c1 -n0 python bench.py

You might also want to disable any swap files/partitions so that swapping
doesn't influence performance.  (The programs will just die if they try to
allocate too much memory.)

To run the throughput benchmark:

    $ cd hash-table-shootout
    $ mkdir build_throughput
    $ make -f MakefileThroughput
    $ python bench_throughput.py

The results can be found in `output_throughput`. I just hacked up my own charts, but I might add a similar utility to generate charts like Nick's.

You can use the same `nice`/`ionice` command line as above to run it at highest priority, but replace `bench.py` with `bench_throughput.py`, naturally.

Copyright Information
=====================

Modified by Timon Karnezos in 2011.

Originally written by Nick Welch in 2010.

No copyright.  This work is dedicated to the public domain.

For full details, see http://creativecommons.org/publicdomain/zero/1.0/
