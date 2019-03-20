// This file is part of Fuxedo
// Copyright (C) 2017 Aivars Kalvans <aivars.kalvans@gmail.com>

#include <xatmi.h>

#include <cstdarg>
#include <cstdio>

namespace fux {
namespace atmi {

static thread_local int tperrno_ = 0;
static thread_local long tpurcode_ = 0;

static thread_local char tplasterr_[1024] = {0};

void set_tperrno(int err, const char *fmt, ...) {
  tperrno_ = err;
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(tplasterr_, sizeof(tplasterr_), fmt, ap);
  va_end(ap);
}

void reset_tperrno() {
  tperrno_ = 0;
  tplasterr_[0] = '\0';
}
}  // namespace atmi
}  // namespace fux

int *_tls_tperrno() { return &fux::atmi::tperrno_; }
long *_tls_tpurcode() { return &fux::atmi::tpurcode_; }

char *tpstrerror(int err) {
  switch (err) {
    case TPEBADDESC:
    case TPEBLOCK:
    case TPEINVAL:
    case TPELIMIT:
    case TPENOENT:
    case TPEOS:
    case TPEPROTO:
    case TPESVCERR:
    case TPESVCFAIL:
    case TPESYSTEM:
    case TPETIME:
    case TPETRAN:
    case TPGOTSIG:
    case TPEITYPE:
    case TPEOTYPE:
    case TPEEVENT:
    case TPEMATCH:
    default:
      return const_cast<char *>("?");
  }
}
