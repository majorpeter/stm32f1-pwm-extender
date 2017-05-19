/*
 * LedNode.h
 *
 *  Created on: 2017. máj. 19.
 *      Author: peti
 */

#ifndef LEDNODE_H_
#define LEDNODE_H_

#include "mprotocol-nodes/Node.h"

class LedNode: public Node {
	DECLARE_PROP_BOOL_RW(Green);
public:
	LedNode();
};

#endif /* LEDNODE_H_ */
