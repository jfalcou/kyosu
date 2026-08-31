#!/usr/bin/env python3
##======================================================================================================================
##  Kyosu - Complex Without Complexes
##  Copyright : KYOSU Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
"""Drop eve's symbols from the generated search index.

Reading eve.tag is what makes the eve:: references in kyosu's documentation resolve, and it also hands doxygen every
symbol eve documents. Those end up in kyosu's search box, where three results out of five lead to another library's
site. Doxygen has no setting for this: ALLEXTERNALS, EXTERNAL_GROUPS and EXTERNAL_PAGES govern the index pages and
leave the search index alone.

A name kyosu and eve both document - abs, sqrt, majorant - carries one target each, so an entry is rewritten rather
than removed, and removed only when nothing of kyosu's is left in it.
"""

import re
import sys
from pathlib import Path

## One search entry per line: ['id',['name',['target',N,'context'],['target',N]]], where the context is sometimes
## absent and a name such as operator[] carries brackets of its own, so the targets are matched rather than the
## brackets counted.
ENTRY = re.compile(r"^(\s*\['[^']*',\['[^']*',)(.*?)(\]\],?)$")
TARGET = re.compile(r"\['([^']*)',\s*\d+\s*(?:,\s*'[^']*')?,?\]")


def external(target: str) -> bool:
    return target.startswith("http://") or target.startswith("https://")


def strip(line: str) -> str | None:
    """The line without its external targets, or None when only external ones were in it."""
    match = ENTRY.match(line)
    if not match:
        return line

    head, body, tail = match.groups()
    targets = TARGET.findall(body)

    if not targets:
        return line
    if not any(external(t) for t in targets):
        return line
    if all(external(t) for t in targets):
        return None

    kept = [m.group(0) for m in TARGET.finditer(body) if not external(m.group(1))]

    return head + ",".join(kept) + tail


def main(directory: str) -> int:
    files = sorted(Path(directory).glob("*.js"))
    if not files:
        print(f"[kyosu] - no search index under {directory}", file=sys.stderr)
        return 1

    removed = rewritten = 0

    for path in files:
        out = []
        for line in path.read_text(encoding="utf-8").split("\n"):
            stripped = strip(line)
            if stripped is None:
                removed += 1
            else:
                rewritten += stripped != line
                out.append(stripped)

        ## A file whose entries all came from eve keeps its array, empty: the search javascript loads it by name.
        path.write_text("\n".join(out), encoding="utf-8")

    print(f"[kyosu] - search index: {removed} external entries dropped, {rewritten} trimmed")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1] if len(sys.argv) > 1 else "."))
