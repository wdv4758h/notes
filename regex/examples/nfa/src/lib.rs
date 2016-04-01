//
// A Rust rewrite of regular expression implementation
// from https://swtch.com/~rsc/regexp/nfa.c.txt
//
// Supports only ( | ) * + ?.  No escapes.
// Compiles to NFA and then simulates NFA
// using Thompson's algorithm.
//
// See also http://swtch.com/~rsc/regexp/ and
// Thompson, Ken.  Regular Expression Search Algorithm,
// Communications of the ACM 11(6) (June 1968), pp. 419-422.
//
// Copyright (c) 2007 Russ Cox.
// Copyright (c) 2016 Chiu-Hsiang Hsu.
// Can be distributed under the MIT license, see bottom of file.
//

/// Convert infix regex to postfix notation.
/// Insert . as explicit concatenation operator.
///
/// "a(bb)+a" => "abb.+.a."
/// in this place, '.' means concatenation
/// "abb.+.a"
/// => take 'a' => ['a']
/// => take 'b' => ['a', 'b']
/// => take 'b' => ['a', 'b', 'b']
/// => take '.' => pop 2, concatenate, push => ['a', "bb"]
/// => take '+' => ['a', "bb+"]
/// => take '.' => ["a(bb+)"]
/// => take 'a' => ["a(bb+)", 'a']
/// => take '.' => ["a(bb+)a"]
pub fn regex_to_postfix(regex: String) -> Option<String> {

    // this is the context
    struct Counter {
        nalt: u32,  // number of alternatives
        natom: u32, // number of atoms
    };

    let mut counters = vec![];  // counter stack

    let mut counter = Counter { nalt: 0, natom: 0 };    // current counter
    let mut result = "".to_string();

    for i in regex.chars() {
        match i {
            '(' => {
                // special charactor to open a group,
                // concatenate atoms first,
                // then make a new context and do context switch
                if counter.natom > 1 {
                    counter.natom -= 1;
                    result.push('.');
                }
                counters.push(counter);
                counter = Counter { nalt: 0, natom: 0 };
            },
            '|' => {
                // special charactor for alternative path
                // if there is no atom in current context,
                // it must be a WRONG regular expression,
                // concatenate atoms first,
                // then add the counter
                if counter.natom == 0 {
                    return None;
                }

                // while(--natom > 0)
                for _ in 0..(counter.natom-1) {
                    result.push('.');
                }
                counter.natom = 0;

                counter.nalt += 1;
            },
            ')' => {
                // special charactor to close a group,
                // concatenate current atoms first,
                // concatenate alternative paths second,
                // drop context, resume previous context,
                // add the counter
                if counters.len() == 0 ||
                   counter.natom == 0 {
                    return None;
                }

                // while(--natom > 0)
                for _ in 0..(counter.natom-1) {
                    result.push('.');
                }

                // for(; nalt > 0; nalt--)
                for _ in 0..(counter.nalt) {
                    result.push('|');
                }

                counter = counters.pop().unwrap();
                counter.natom += 1;
            },
            '*' | '+' | '?' => {
                // special characters for repeat
                // if there is no atom in current context,
                // it must be a WRONG regular expression
                if counter.natom == 0 {
                    return None;
                }
                result.push(i);
            },
            _   => {
                // nothing special,
                // save current char (atom) and add the counter,
                // if there are atoms larger than 2,
                // then add an concatenation symbol ('.')
                if counter.natom > 1 {
                    counter.natom -= 1;
                    result.push('.');
                }
                result.push(i);
                counter.natom += 1;
            },
        }
    }

    // if there are counters waiting to be solved,
    // the it must have non-matching bracket,
    // it must be a WRONG regular expression
    if counters.len() > 0 {
        return None;
    }

    // clean current context,
    // concatenate current atoms first,
    // concatenate alternative paths second,
    for _ in 0..(counter.natom-1) {
        result.push('.');
    }

    // for(; nalt > 0; nalt--)
    for _ in 0..(counter.nalt) {
        result.push('|');
    }

    Some(result)
}


//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall
// be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
// KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
