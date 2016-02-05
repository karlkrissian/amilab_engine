
facade_class1 = 'boost::iterator_facade<' + \
                 'boost::filesystem::directory_iterator, ' + \
                 'boost::filesystem::directory_entry, ' + \
                 'boost::single_pass_traversal_tag, ' + \
                 'boost::filesystem::directory_entry&, ' + \
                 'long>'

facade_class2 = 'boost::iterator_facade<' + \
                 'boost::filesystem::recursive_directory_iterator, ' + \
                 'boost::filesystem::directory_entry, ' + \
                 'boost::single_pass_traversal_tag, ' + \
                 'boost::filesystem::directory_entry&, ' + \
                 'long>'

facade_class3 = 'boost::iterator_facade<' + \
                  'boost::filesystem::path::iterator, ' + \
                  'boost::filesystem::path const, ' + \
                  'boost::bidirectional_traversal_tag, ' + \
                  'boost::filesystem::path const&, ' + \
                  'long>'

# Need to get rid of non-implemented method
members_blacklist=[
    # weird method?: instanciated template
    'boost::filesystem::path::path<char [20]>(char const (&) [20], '+\
      'boost::enable_if<boost::filesystem::path_traits::is_pathable<boost::decay<char [20]>::type>, void>::type*)',
    facade_class1+'::operator--(int)',
    facade_class1+'::operator-(long)',
    facade_class1+'::operator-(long) const',
    facade_class1+'::operator--()',
    facade_class1+'::operator+=(long)',
    facade_class1+'::operator-=(long)',
    facade_class2+'::operator--(int)',
    facade_class2+'::operator-(long)',
    facade_class2+'::operator-(long) const',
    facade_class2+'::operator--()',
    facade_class2+'::operator+=(long)',
    facade_class2+'::operator-=(long)',
    facade_class3+'::operator+=(long)',
    facade_class3+'::operator-=(long)',
    facade_class3+'::operator-(long)',
    facade_class3+'::operator-(long) const',
    # need to black list members that return a reference and that are not available in C++11
    'std::complex<float>::real()',
    'std::complex<float>::imag()',
]
