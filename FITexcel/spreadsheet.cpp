#include "spreadsheet.h"

CSpreadsheet::CSpreadsheet ():
    map() {}

CSpreadsheet::CSpreadsheet( CSpreadsheet & arg ):
    map() {
    std::map<CPos, std::unique_ptr<ASTNode>> newMap;
    for ( const auto & cell : arg.map )
        map . emplace ( cell.first, cell.second->copy( std::pair(0, 0) ) );
}

CSpreadsheet & CSpreadsheet::operator = ( CSpreadsheet & arg ) {
    map.clear();
    for ( const auto & cell : arg.map )
        map . emplace ( cell.first, cell.second->copy( std::pair(0, 0) ));
    return *this;
}

bool CSpreadsheet::load ( std::istream & is ) {
    map.clear();

    char c;
    while ( !is.fail() ) {
        std::string cell = ""; 

        is.get(c);
        
        if ( is.eof() )
            return true;

        if ( is.fail() || (!isalpha(c) && c != '$'))
            return false;

        cell += c;
        
        while (is.get(c) && isalpha(c) && !is.fail() && !is.eof() )
            cell += c;

        if ((!isnumber(c) && c != '$' ) || is.fail() || is.eof() )
            return false;

        cell += c;

        while (is.get(c) && isnumber(c) && !is.fail() && !is.eof() )
            cell += c;

        if (c == '$')
            cell += c;
        else if ( c != '-' )
            return false;

        std::string sizeStr;
        while (is.get(c) && isnumber(c))
            sizeStr += c;
        
        if (c != '-')
            return false;

        int size = std::stoi(sizeStr);
        std::string value = "=";
        for (int i = 0; i < size; ++i) {
            if ( is.fail() || !is.get(c) )
                return false;
            value += c;
        }

        this->setCell(CPos(cell), value);

        if (is.eof())
            return true;
    }

    if ( is.fail() )
        return false;

    return true;
}

bool CSpreadsheet::save ( std::ostream & os ) const {
    for ( const auto & cell : map ) {
        if ( os.fail() )
            return false;
        std::ostringstream oss;
        cell.second->print( oss );
        os << cell.first << "-" << oss.str().size() << "-" << oss.str();
    }

    if ( os.fail() )
        return false;

    return true;
}

bool CSpreadsheet::setCell ( CPos pos, std::string contents ) {
    ASTBuilder builder ( contents );
    std::unique_ptr<ASTNode> root;
    builder.getLast(root);
    root->print ( std::cout );
    std::cout << std::endl;
    auto it = map.find( pos );
    if ( it == map.end() ) 
        map . emplace ( pos, std::move(root));
    else
        it->second = std::move(root);
    return true;
}

CValue CSpreadsheet::getValue ( CPos pos ) {
    auto it = map.find(pos);
    if ( it != map.end() ) {
        std::set<CPos> visited;
        std::set<CPos> stack;
//        visited . emplace ( pos );
//        stack . emplace ( pos );
        if ( it->second->detectCycle ( pos, visited, stack, this->map ) )
            return std::monostate{};
        it->second->print ( std::cout );
        std::cout << std::endl;
        return it->second->evaluate( map );
    }
    return std::monostate{};
}

void CSpreadsheet::copyRect ( CPos dst, CPos src, int w, int h ) {
    std::map<CPos, std::unique_ptr<ASTNode>> tmpMap;
    std::vector<CPos> srcPositions = {};
    rectIterationSize ( srcPositions, src, w, h );
    std::vector<CPos> dstPositions = {};
    rectIterationSize ( dstPositions, dst, w, h );
    for ( size_t i = 0; i < srcPositions.size(); i++ ) {
        auto it = map . find( srcPositions[i] );
        if ( it == map.end() )  
            continue;
        auto delta = dstPositions[i] - srcPositions[i];
        auto tmp = it->second->copy( delta );
        tmpMap . emplace ( dstPositions[i], std::move(tmp) );
    }

    for ( const auto & cell : tmpMap ) {
        auto it = map.find(cell.first); 
        if ( it == map.end() ) {
            auto tmp = cell.second->copy( std::pair(0, 0));
            map . emplace ( cell.first, std::move(tmp));
        }   
        else {
            it->second = (cell.second->copy( std::pair(0, 0) ));
        }
    }
}

bool CSpreadsheet::containsCycle ( const CPos & pos, const std::map<CPos, std::set<CPos>> & graph, std::set<CPos> & visited, std::set<CPos> & stack ) const {
    auto vIt = visited . find ( pos );
    if ( vIt == visited . end () ) {
        visited . emplace ( pos );
        stack . emplace ( pos );

        auto gIt = graph . find ( pos );
        for ( const auto & neigh : gIt->second ) {
//            auto mIt = map . find ( neigh );
//            if ( mIt == map . end () )
//                continue;            
            auto vIt = visited . find ( neigh );
            auto sIt = stack . find ( neigh ); 

            if ( vIt == visited . end() && containsCycle(neigh, graph, visited, stack) )     
                return true;
            else if ( sIt != stack . end() )
                return true;      
        }
    }
    stack . erase ( pos );
    return false;
}
