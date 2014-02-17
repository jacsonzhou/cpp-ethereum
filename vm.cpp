/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file state.cpp
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 * State test functions.
 */

#include <boost/algorithm/string.hpp>
#include <secp256k1.h>
#include <BlockChain.h>
#include <State.h>
#include <Defaults.h>
#include <Instruction.h>
using namespace std;
using namespace eth;

namespace eth
{
template <> class UnitTest<1>
{
public:
	int operator()()
	{
		KeyPair p = KeyPair::create();
		Overlay o;
		State s(p.address(), o);

		cout << s;

		s.addBalance(p.address(), Uether);

		cout << s;

		Transaction c;

		c.receiveAddress = Address();
		c.nonce = 0;
		c.data = assemble("txsender load txvalue add txsender store stop");
		c.value = ether;
		c.sign(p.secret());
		s.execute(c.rlp());
		Address ca = right160(c.sha3());

		cout << s;

		s.commit();

		cout << s;

		cout << s.m_db;

		c.receiveAddress = ca;
		c.nonce = 1;
		c.data = {};
		c.value = 69 * wei;
		c.sign(p.secret());
		s.execute(c.rlp());

		cout << s;

		return 0;
	}
};
}

int vmTest()
{
	return UnitTest<1>()();
}

