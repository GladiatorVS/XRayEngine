////////////////////////////////////////////////////////////////////////////
//	Module 		: game_graph_builder.h
//	Created 	: 14.12.2005
//  Modified 	: 14.12.2005
//	Author		: Dmitriy Iassenev
//	Description : Game graph builder
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../XrEngine/xrLevel.h"
#include "alife_space.h"
#include "game_graph.h"
#include "graph_vertex.h"
#include "graph_edge.h"
#include "graph_abstract.h"

struct ISE_Abstract;
class CLevelGraph;
class CGameLevelCrossTable;

template <
	typename _data_type,
	typename _edge_weight_type,
	typename _vertex_id_type
>
class CGraphAbstract;

namespace GameGraph 
{
	struct CVertex;
};

class NET_Packet;

class CGraphEngine;

class CGameGraphBuilder 
{
private:
	typedef GameGraph::CVertex						vertex_type;
	typedef CGraphAbstract<vertex_type,float,u32>	graph_type;
	typedef xr_vector<xr_vector<u32> >				DISTANCES;
	typedef std::pair<u32,u32>						PAIR;
	typedef std::pair<float,PAIR>					TRIPPLE;
	typedef xr_vector<TRIPPLE>						TRIPPLES;

private:
	LPCSTR					m_graph_name;
	LPCSTR					m_cross_table_name;

private:
	shared_str				m_level_name;

private:
	CLevelGraph				*m_level_graph;
	graph_type				*m_graph;
	xrGUID					m_graph_guid;
	// cross table generation stuff
	xr_vector<bool>			m_marks;
	xr_vector<u32>			m_mark_stack;
	DISTANCES				m_distances;
	xr_vector<u32>			m_current_fringe;
	xr_vector<u32>			m_next_fringe;
	xr_vector<u32>			m_results;
	// cross table itself
	CGameLevelCrossTable	*m_cross_table;
	TRIPPLES				m_tripples;
	xr_vector<u32>			m_path;
	CGraphEngine			*m_graph_engine;
	GameGraph::CHeader		m_graph_header;
	GameGraph::CEdge		*m_edges;
	GameGraph::CVertex*		m_vertexs;

private:
			void		create_graph				();
			void		load_level_graph			();
			void		load_graph_point			(ISE_Abstract* entity);
			void		load_graph_points			();

private:
			void		mark_vertices				(u32 level_vertex_id);
			void		fill_marks					();
			void		fill_distances				();
			void		recursive_update			(const u32 &index);
			void		iterate_distances			();
			void		build_cross_table			();
			
private:
			void		fill_neighbours				(const u32 &game_vertex_id);
			float		path_distance				(const u32 &game_vertex_id0, const u32 &game_vertex_id1);
			void		generate_edges				(const u32 &vertex_id);
			void		generate_edges				();
			void		connectivity_check			();
			void		create_tripples				();
			void		process_tripple				(const TRIPPLE &tripple);
			void		optimize_graph				();
			void		build_game_graph			();

private:
	IC		CLevelGraph				&level_graph	() const;
	IC		graph_type				&graph			() const;
public:
	IC		CGameLevelCrossTable& cross() const;
			GameGraph::CEdge* graph_edges() const;
			GameGraph::CVertex* graph_vertex() const;
			GameGraph::CHeader* graph_header() const;


						CGameGraphBuilder			();
						~CGameGraphBuilder			();
			void		build_graph					();
};

#include "game_graph_builder_inline.h"