Name:           libopalevents
Version:        1
Release:        0%{?dist}
Summary:        PEL structure reader and parser

License:        LGPLv2
URL:            https://github.com/open-power/libopalevents
Source0:        https://github.com/open-power/libopalevents/archive/master.tar.gz
BuildRequires: autoconf automake libtool 
#Requires:       

%description 
PEL structure reader and parser
library to aid in reading, parsing and printing platform event log structures
 from files.



%package        devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description    devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.


%prep

%setup -qn %{name}-master
autoreconf -if

%build
%configure --disable-static --prefix=/usr
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
%make_install
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%doc
%{_libdir}/*.so.*

%files devel
%doc
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/pkgconfig/libopalevents.pc


%changelog
* Wed Apr  8 2015 Cyril Bur <cyril.bur@au1.ibm.com> - 1
- Inital verion of the package
